#include "stdafx.h"
#include "CompileGetFunction.h"
#include "CompileCondition.h"
#include "CompileEquals.h"
#include "CompileFactory.h"
#include "DirectFunctionCall.h"
#include "DoNothingNode.h"
#include "FunctionCall.h"
#include "FunctionHandler.h"
#include "TokenExpectation.h"

#define szGetFromReturnValue "getFromReturnValue"
#define SET_ID_TO_RT "IdentifierToReturnValue"

CompileGetFunction::CompileGetFunction()
{
	_paramTokens		= make_shared<vector<shared_ptr<Token>>>();
	variableMap			= make_unique<map<string, string>>();
	_returnToken		= nullptr;
	_bodyTokens			= make_shared<LinkedList>();
	_compiledStatement	= make_shared<LinkedActionList>();
	_body				= make_shared<LinkedActionList>();
	_parameters			= make_shared<LinkedActionList>();
	_functionParams		= make_shared<LinkedActionList>();
	_functionCall		= make_shared<LinkedActionList>();
	_compiledStatement->add(make_shared<DoNothingNode>());
}

void CompileGetFunction::compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore)
{
	shared_ptr<Token> current = make_shared<Token>(begin);
	int level = begin.getLevel();
	shared_ptr<Token> bodyEnd = nullptr;

	unique_ptr<list<shared_ptr<TokenExpectation>>> expected = make_unique<list<shared_ptr<TokenExpectation>>>();
	expected->push_back(make_shared<TokenExpectation>(level, Token::FUNCTION_DECLARE_OPEN));
	expected->push_back(make_shared<TokenExpectation>(level, Token::FUNCTION_CALL));

	for (shared_ptr<TokenExpectation> expectation : *expected)
	{
		while (current->getEnum() == Token::NEWLINE) 
		{
			current = make_shared<Token>(current->next); // Todo fix tokenizer, will throw error soon
		}

		if (expectation->getLevel() == level)
		{
			if (current->getEnum() == Token::FUNCTION_CALL) 
			{
				for (auto p : *FunctionHandler::getInstance()->getFunctions()) 
				{
					if (p->getName() == current->getText()) 
					{
						_name			= p->getName();
						_params			= p->getParams();
						_paramTokens	= p->getParamTokens();
						_bodyTokens		= p->getBody();
						_returnToken	= p->getReturn();
						userDefined		= p->isUserDefined();

						break;
					}
				}
			}

			if (current->getEnum() != expectation->getTokenType()) 
			{
				ErrorHandler::getInstance()->addError(Error{ "", ".md", current->getLevel(), current->getPositie(), Error::error }, expectation->getTokenType(), current->getEnum());
				begin = end;

				break;
			}
			else
			{
				current = make_shared<Token>(current->next); // Todo fix tokenizer, will throw error soon
			}
		}
	}

	if (!userDefined)
	{
		compileNotUserDefined(cTokenList, *current, end);
	}
	else
	{
		compileUserDefined(cTokenList, *current, end);
	}
	connectLists();
	begin = *current;
	shared_ptr<LinkedActionList> list = make_shared<LinkedActionList>(listActionNodes);
	list->insertBefore(make_shared<ActionNode>(actionBefore), _compiledStatement);
	listActionNodes = *list;
}

shared_ptr<Compiler> CompileGetFunction::create()
{
	return make_shared<CompileGetFunction>();
}

void CompileGetFunction::compileNotUserDefined(LinkedList& cTokenList, Token& begin, Token& end)
{
	shared_ptr<Token> current = make_shared<Token>(begin);
	unique_ptr<vector<string>> parameters = make_unique<vector<string>>();
	_functionParams->add(make_shared<DoNothingNode>());

	while (current->getEnum() != Token::FUNCTION_DECLARE_CLOSE) 
	{
		// compile condition
		shared_ptr<Token> seperator = current;

		while (seperator->getEnum() != Token::AND_PARA || seperator->getEnum() != Token::FUNCTION_DECLARE_CLOSE) 
		{
			if (seperator->getEnum() == Token::AND_PARA || seperator->getEnum() == Token::FUNCTION_DECLARE_CLOSE)
			{
				break;
			}
			seperator = make_shared<Token>(seperator->next); // Todo fix tokenizer, will throw error soon
		}
		shared_ptr<CompileCondition> condition = make_shared<CompileCondition>();
		condition->compile(cTokenList, *current, *seperator, *_functionParams, *_functionParams->getLast());

		// Create direct functioncall
		string sBuffer;
		string tempVar = getNextLocalVariableName(sBuffer);
		shared_ptr<DirectFunctionCall> pDirectFunction = make_shared<DirectFunctionCall>();
		pDirectFunction->setArraySize(2);
		pDirectFunction->setAt(0, szGetFromReturnValue);
		pDirectFunction->setAt(1, tempVar.c_str());
		_functionParams->insertBefore(_functionParams->getLast(), pDirectFunction);
		parameters->push_back(tempVar);

		if (current->getEnum() == Token::AND_PARA)
		{
			current = make_shared<Token>(current->next); // Todo fix tokenizer, will throw error soon
		}
	}

	if (parameters->size() > _params.size()) 
	{
		ErrorHandler::getInstance()->addError(Error{ _name + " has more parameters than expected", ".md", current->getLineNumber(), current->getPositie(), Error::error });
	}

	if (parameters->size() < _params.size()) 
	{
		ErrorHandler::getInstance()->addError(Error{ _name + " has less parameters than expected", ".md", current->getLineNumber(), current->getPositie(), Error::error });
	}
	shared_ptr<FunctionCall> pFunction = make_shared<FunctionCall>();
	pFunction->setArraySize(parameters->size()+1);
	pFunction->setAt(0, _name.c_str());

	for (int n = 0; (size_t)n < parameters->size(); n++)
	{
		pFunction->setAt(n + 1, (*parameters)[n].c_str());
	}
	_functionCall->insertLast(pFunction);
	begin = *current->next;
}

void CompileGetFunction::compileUserDefined(LinkedList& cTokenList, Token& begin, Token& end)
{
	unique_ptr<CompileFactory> factory = make_unique<CompileFactory>();
	shared_ptr<Token> current = make_shared<Token>(begin);
	unique_ptr<vector<shared_ptr<LinkedList>>> paramList = make_unique<vector<shared_ptr<LinkedList>>>();
	int count = 0;

	if (_params.size() > 0) 
	{
		_parameters->add(make_shared<DoNothingNode>());
		shared_ptr<LinkedList> param = make_shared<LinkedList>();

		do 
		{
			if ((size_t)count > _params.size() - 1)
			{
				ErrorHandler::getInstance()->addError(Error{ _name + " has more parameters than expected", ".md", current->getLineNumber(), current->getPositie(), Error::error });

				break;
			}

			if (current->getEnum() != Token::AND_PARA)
			{
				param->add(new Token(*current));
			}
			else 
			{
				param->last->next = nullptr;
				param->first->previous = nullptr;

				connectParams(_paramTokens->at(count), *param);
				paramList->push_back(param);
				param = make_shared<LinkedList>();
				count++;
			}
			current = make_shared<Token>(current->next); // Todo fix tokenizer, will throw error soon

			if (current->getEnum() == Token::FUNCTION_DECLARE_CLOSE) 
			{
				param->last->next = nullptr;
				param->first->previous = nullptr;
				connectParams(_paramTokens->at(count), *param);
				paramList->push_back(param);
				param = make_shared<LinkedList>();
			}
		}
		while (current->getEnum() != Token::FUNCTION_DECLARE_CLOSE);
	}

	if ((size_t)count < _params.size() - 1) 
	{
		ErrorHandler::getInstance()->addError(Error{ _name + " has less parameters than expected", ".md", current->getLineNumber(), current->getPositie(), Error::error });
	}

	for (auto p : *paramList) 
	{
		shared_ptr<CompileEquals> condition = make_shared<CompileEquals>();
		condition->compile(*p, *p->first, *p->last, *_parameters, *_parameters->getLast());
	}

	if (_returnToken) 
	{
		_returnToken = make_shared<Token>(*_returnToken);
		shared_ptr<LinkedActionList> rValue = make_shared<LinkedActionList>();
		shared_ptr<CompileCondition> con = make_shared<CompileCondition>();
		con->compile(cTokenList, *_returnToken, *_returnToken, *rValue, *rValue->getLast());

		string sBuffer;
		shared_ptr<DirectFunctionCall> pDirectFunction = make_shared<DirectFunctionCall>();
		string tempVar = getNextLocalVariableName(sBuffer);
		pDirectFunction->setArraySize(2);
		pDirectFunction->setAt(0, szGetFromReturnValue);
		pDirectFunction->setAt(1, tempVar.c_str());
		rValue->insertBefore(pDirectFunction, rValue->getLast());
		_body->add(rValue);
	}
	shared_ptr<LinkedList> body = make_shared<LinkedList>(*_bodyTokens);
	changeVariables(*body);
	shared_ptr<Token> currentBody = make_shared<Token>(body->first); // Todo fix tokenizer, will throw error soon
	_body->add(make_shared<DoNothingNode>());

	while (currentBody != nullptr) 
	{
		if (currentBody->getEnum() == Token::FUNCTION_CLOSE)
		{
			currentBody = make_shared<Token>(currentBody->next); // Todo fix tokenizer, will throw error soon

			break;
		}
		shared_ptr<Compiler> compiledBodyPart = factory->createCompileStatement(*currentBody);

		if (compiledBodyPart != nullptr) 
		{
			compiledBodyPart->compile(*_bodyTokens, *currentBody, *body->last, *_body, *_body->getLast());
		}
		else
		{
			currentBody = make_shared<Token>(currentBody->next); // Todo fix tokenizer, will throw error soon
		}
	}

	if (_returnToken) 
	{
		string sBuffer;
		string tempVar = getNextLocalVariableName(sBuffer);
		changeVariable(*_returnToken);
		shared_ptr<DirectFunctionCall> directFunctionCall = make_shared<DirectFunctionCall>();
		directFunctionCall->setArraySize(2);
		directFunctionCall->setAt(0, SET_ID_TO_RT);
		directFunctionCall->setAt(1, _returnToken->getText().c_str());
		_body->insertBefore(_body->getLast(), directFunctionCall);
	}
	begin = *current;
}

void CompileGetFunction::changeVariables(LinkedList& list) 
{
	shared_ptr<Token> current = make_shared<Token>(list.first); // Todo fix tokenizer, will throw error soon

	while (current != nullptr) 
	{
		changeVariable(*current);
		current = make_shared<Token>(current->next); // Todo fix tokenizer, will throw error soon
	}
}

void CompileGetFunction::changeVariable(Token& token) 
{
	string sBuffer;

	if (token.getEnum() == Token::IDENTIFIER)
	{
		string localVar;

		if (variableMap->count(token.getText()) > 0) 
		{
			localVar = (*variableMap)[token.getText()];
		}
		else 
		{
			localVar = getNextLocalVariableName(sBuffer) + "_" + token.getText();
			(*variableMap)[token.getText()] = localVar;
		}
		token.setText(localVar);
	}	
}

void CompileGetFunction::connectParams(shared_ptr<Token> param, LinkedList& paramlist)
{
	shared_ptr<Token> connectToken = make_shared<Token>();
	shared_ptr<Token> nParam = param;
	changeVariable(*nParam);
	connectToken->setEnum(Token::EQUALS);
	connectToken->setLevel(nParam->getLevel());
	connectToken->setPositie(-1);
	connectToken->setPositieInList(-1);
	connectToken->setRegelnummer(-1);
	connectToken->setText("=");
	shared_ptr<LinkedList> templist = make_shared<LinkedList>();
	templist->add(&*nParam); // Todo fix tokenizer, will throw error soon
	templist->add(&*connectToken); // Todo fix tokenizer, will throw error soon
	shared_ptr<Token> temp = make_shared<Token>(paramlist.first); // Todo fix tokenizer, will throw error soon

	while (temp != nullptr) 
	{
		templist->add(&*temp); // Todo fix tokenizer, will throw error soon
		temp = make_shared<Token>(temp->next); // Todo fix tokenizer, will throw error soon
	}
	connectToken = make_shared<Token>();
	connectToken->setEnum(Token::NEWLINE);
	connectToken->setLevel(nParam->getLevel());
	connectToken->setPositie(-1);
	connectToken->setPositieInList(-1);
	connectToken->setRegelnummer(-1);
	connectToken->setText("\n");
	templist->add(&*connectToken); // Todo fix tokenizer, will throw error soon
	
	temp = make_shared<Token>(templist->first); // Todo fix tokenizer, will throw error soon
	paramlist = *make_shared<LinkedList>();

	while (temp != nullptr) 
	{
		paramlist.add(&*temp); // Todo fix tokenizer, will throw error soon
		temp = make_shared<Token>(temp->next); // Todo fix tokenizer, will throw error soon
	}
}

void CompileGetFunction::connectLists()
{
	if (userDefined)
	{
		if (_parameters->getCount() > 0)
		{
			_compiledStatement->add(_parameters);
		}
		_compiledStatement->add(_body);
	}
	else
	{
		_compiledStatement->add(_functionParams);
		_compiledStatement->add(_functionCall);
	}
}