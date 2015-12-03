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
	_returnToken		= nullptr;
	_bodyTokens			= make_shared<LinkedList>();
	_compiledStatement	= make_shared<LinkedActionList>();
	_body				= make_shared<LinkedActionList>();
	_parameters			= make_shared<LinkedActionList>();
	_functionParams		= make_shared<LinkedActionList>();
	_functionCall		= make_shared<LinkedActionList>();
	_compiledStatement->add(make_shared<DoNothingNode>());
}

void CompileGetFunction::compile(shared_ptr<LinkedList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end, 
								 shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore)
{
	shared_ptr<Token> current = begin;
	int level = begin->getLevel();
	shared_ptr<Token> bodyEnd = nullptr;

	list<shared_ptr<TokenExpectation>> expected;
	expected.push_back(make_shared<TokenExpectation>(level, Token::FUNCTION_DECLARE_OPEN));
	expected.push_back(make_shared<TokenExpectation>(level, Token::FUNCTION_CALL));

	for (shared_ptr<TokenExpectation> expectation : expected)
	{
		while (current->getEnum() == Token::NEWLINE) 
		{
			current = shared_ptr<Token>(current->next); // Todo fix tokenizer, will throw error soon
		}

		if (expectation->getLevel() == level)
		{
			if (current->getEnum() == Token::FUNCTION_CALL) 
			{
				for (shared_ptr<Function> p : FunctionHandler::getInstance()->getFunctions()) 
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
				ErrorHandler::getInstance()->addError(make_shared<Error>("", ".md", current->getLevel(), current->getPositie(), ErrorType::error), 
													  expectation->getTokenType(), current->getEnum());
				begin = end;

				break;
			}
			else
			{
				current = shared_ptr<Token>(current->next); // Todo fix tokenizer, will throw error soon
			}
		}
	}

	if (!userDefined)
	{
		compileNotUserDefined(tokenList, current, end);
	}
	else
	{
		compileUserDefined(tokenList, current, end);
	}
	connectLists();
	begin = current;
	shared_ptr<LinkedActionList> list = listActionNodes;
	list->insertBefore(actionBefore, _compiledStatement);
	listActionNodes = list;
}

shared_ptr<Compiler> CompileGetFunction::create()
{
	return make_shared<CompileGetFunction>();
}

void CompileGetFunction::compileNotUserDefined(shared_ptr<LinkedList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end)
{
	shared_ptr<Token> current = begin;
	vector<string> parameters;
	_functionParams->add(make_shared<DoNothingNode>());

	while (current->getEnum() != Token::FUNCTION_DECLARE_CLOSE) 
	{
		// Compile condition
		shared_ptr<Token> seperator = current;
		stack<Token::iToken> stack;

		while (stack.size() >= 0 && (seperator->getEnum() != Token::AND_PARA || seperator->getEnum() != Token::FUNCTION_DECLARE_CLOSE)) 
		{
			if (seperator->getEnum() == Token::FUNCTION_DECLARE_OPEN)
			{
				stack.push(seperator->getEnum());
			}
			else if (seperator->getEnum() == Token::FUNCTION_DECLARE_CLOSE && stack.size() > 0) 
			{
				stack.pop();
			}
			else if (stack.size() == 0 && (seperator->getEnum() == Token::AND_PARA || seperator->getEnum() == Token::FUNCTION_DECLARE_CLOSE))
			{
				break;
			}

			seperator = shared_ptr<Token>(seperator->next);
		}
		shared_ptr<CompileCondition> condition = make_shared<CompileCondition>();
		condition->compile(tokenList, current, seperator, _functionParams, _functionParams->getLast());

		// Create direct functioncall
		string sBuffer;
		string tempVar = getNextLocalVariableName(sBuffer);
		shared_ptr<DirectFunctionCall> pDirectFunction = make_shared<DirectFunctionCall>();
		pDirectFunction->setArraySize(2);
		pDirectFunction->setAt(0, szGetFromReturnValue);
		pDirectFunction->setAt(1, tempVar.c_str());
		_functionParams->insertBefore(_functionParams->getLast(), pDirectFunction);
		parameters.push_back(tempVar);

		if (current->getEnum() == Token::AND_PARA)
		{
			current = shared_ptr<Token>(current->next); // Todo fix tokenizer, will throw error soon
		}
	}

	if (parameters.size() > _params.size()) 
	{
		ErrorHandler::getInstance()->addError(make_shared<Error>(_name + " has more parameters than expected", ".md", current->getLineNumber(), 
											  current->getPositie(), ErrorType::error));
	}

	if (parameters.size() < _params.size()) 
	{
		ErrorHandler::getInstance()->addError(make_shared<Error>(_name + " has less parameters than expected", ".md", current->getLineNumber(), 
											 current->getPositie(), ErrorType::error));
	}
	shared_ptr<FunctionCall> pFunction = make_shared<FunctionCall>();
	pFunction->setArraySize(parameters.size()+1);
	pFunction->setAt(0, _name.c_str());

	for (int n = 0; (size_t)n < parameters.size(); n++)
	{
		pFunction->setAt(n + 1, parameters[n].c_str());
	}
	_functionCall->insertLast(pFunction);
	begin = shared_ptr<Token>(current->next); // Todo fix tokenizer, will throw error soon
}

void CompileGetFunction::compileUserDefined(shared_ptr<LinkedList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end)
{
	unique_ptr<CompileFactory> factory = make_unique<CompileFactory>();
	shared_ptr<Token> current = begin;
	shared_ptr<Token> last = end;
	vector<shared_ptr<LinkedList>> paramList;
	int count = 0;

	if (_params.size() > 0) 
	{
		_parameters->add(make_shared<DoNothingNode>());
		shared_ptr<LinkedList> param = make_shared<LinkedList>();
		stack<Token::iToken> stack;

		do 
		{
			if (current->getEnum() == Token::FUNCTION_DECLARE_OPEN)
			{
				stack.push(current->getEnum());
			}
			else if (current->getEnum() == Token::FUNCTION_DECLARE_CLOSE && stack.size() > 0) 
			{
				stack.pop();
			}

			if ((size_t)count > _params.size() - 1)
			{
				ErrorHandler::getInstance()->addError(make_shared<Error>(_name + " has more parameters than expected", ".md", current->getLineNumber(), 
													  current->getPositie(), ErrorType::error));

				break;
			}

			if (stack.size() >= 0) 
			{
				if (stack.size() == 0 && current->getEnum() == Token::AND_PARA) 
				{
					if (param->last != nullptr) 
					{
						param->last->next = nullptr;
						param->first->previous = nullptr;

						connectParams(_paramTokens.at(count), param);
						paramList.push_back(param);
					}
					else {
						ErrorHandler::getInstance()->addError(make_shared<Error>(_name + " expected filling for the parameter", ".md", current->getLineNumber(), 
															  current->getPositie(), ErrorType::error));
					}
					param = make_shared<LinkedList>();
					count++;
				}
				else 
				{
					param->add(new Token(*current));
				}
			}
			current = shared_ptr<Token>(current->next);

			if (stack.size() == 0 && current->getEnum() == Token::FUNCTION_DECLARE_CLOSE) 
			{
				if (param->last != nullptr) 
				{
					param->last->next = nullptr;
					param->first->previous = nullptr;
					connectParams(_paramTokens.at(count), param);
					paramList.push_back(param);
				}
				else {
					ErrorHandler::getInstance()->addError(make_shared<Error>(_name + " expected filling for the parameter", ".md", current->getLineNumber(), 
														  current->getPositie(), ErrorType::error));
				}

				param = make_shared<LinkedList>();

				break;
			}

		} 
		while (current != end);
	}

	if (paramList.size() < _params.size()) 
	{
		ErrorHandler::getInstance()->addError(make_shared<Error>(_name + " has less parameters than expected", ".md", current->getLineNumber(), 
											  current->getPositie(), ErrorType::error));
	}
	else if (paramList.size() > _params.size()) 
	{
		ErrorHandler::getInstance()->addError(make_shared<Error>(_name + " has more parameters than expected", ".md", current->getLineNumber(), 
											  current->getPositie(), ErrorType::error));
	}

	for (shared_ptr<LinkedList> p : paramList) 
	{
		shared_ptr<CompileEquals> condition = make_shared<CompileEquals>();
		condition->compile(p, shared_ptr<Token>(p->first), shared_ptr<Token>(p->last), _parameters, _parameters->getLast()); // Todo fix tokenizer, will throw error soon
	}

	if (_returnToken) 
	{
		_returnToken = _returnToken;
		shared_ptr<LinkedActionList> rValue = make_shared<LinkedActionList>();
		shared_ptr<CompileCondition> con = make_shared<CompileCondition>();
		con->compile(tokenList, _returnToken, _returnToken, rValue, rValue->getLast());

		string sBuffer;
		shared_ptr<DirectFunctionCall> pDirectFunction = make_shared<DirectFunctionCall>();
		string tempVar = getNextLocalVariableName(sBuffer);
		pDirectFunction->setArraySize(2);
		pDirectFunction->setAt(0, szGetFromReturnValue);
		pDirectFunction->setAt(1, tempVar.c_str());
		rValue->insertBefore(pDirectFunction, rValue->getLast());
		_body->add(rValue);
	}
	shared_ptr<LinkedList> body = _bodyTokens;
	changeVariables(body);
	shared_ptr<Token> currentBody = shared_ptr<Token>(body->first); // Todo fix tokenizer, will throw error soon
	_body->add(make_shared<DoNothingNode>());

	while (currentBody != nullptr) 
	{
		if (currentBody->getEnum() == Token::FUNCTION_CLOSE) 
		{
			currentBody = shared_ptr<Token>(currentBody->next); // Todo fix tokenizer, will throw error soon

			break;
		}
		shared_ptr<Compiler> compiledBodyPart = factory->createCompileStatement(currentBody);

		if (compiledBodyPart != nullptr) 
		{
			compiledBodyPart->compile(_bodyTokens, currentBody, shared_ptr<Token>(body->last), _body, _body->getLast()); // Todo fix tokenizer, will throw error soon
		}
		else
		{
			currentBody = shared_ptr<Token>(currentBody->next); // Todo fix tokenizer, will throw error soon
		}
	}

	if (_returnToken) 
	{
		string sBuffer;
		string tempVar = getNextLocalVariableName(sBuffer);
		changeVariable(_returnToken);
		shared_ptr<DirectFunctionCall> directFunctionCall = make_shared<DirectFunctionCall>();
		directFunctionCall->setArraySize(2);
		directFunctionCall->setAt(0, SET_ID_TO_RT);
		directFunctionCall->setAt(1, _returnToken->getText().c_str());
		_body->insertBefore(_body->getLast(), directFunctionCall);
	}
	begin = current;
}

void CompileGetFunction::changeVariables(shared_ptr<LinkedList>& list)
{
	shared_ptr<Token> current = shared_ptr<Token>(list->first); // Todo fix tokenizer, will throw error soon

	while (current != nullptr) 
	{
		changeVariable(current);
		current = shared_ptr<Token>(current->next); // Todo fix tokenizer, will throw error soon
	}
}

void CompileGetFunction::changeVariable(shared_ptr<Token>& token)
{
	string sBuffer;

	if (token->getEnum() == Token::IDENTIFIER)
	{
		string localVar;

		if (variableMap.count(token->getText()) > 0) 
		{
			localVar = variableMap[token->getText()];
		}
		else 
		{
			localVar = getNextLocalVariableName(sBuffer) + "_" + token->getText();
			variableMap[token->getText()] = localVar;
		}
		token->setText(localVar);
	}	
}

void CompileGetFunction::connectParams(shared_ptr<Token> param, shared_ptr<LinkedList>& paramlist)
{
	shared_ptr<Token> connectToken = make_shared<Token>();
	shared_ptr<Token> nParam = param;
	changeVariable(nParam);
	connectToken->setEnum(Token::EQUALS);
	connectToken->setLevel(nParam->getLevel());
	connectToken->setPositie(-1);
	connectToken->setPositieInList(-1);
	connectToken->setRegelnummer(-1);
	connectToken->setText("=");
	shared_ptr<LinkedList> templist = make_shared<LinkedList>();
	templist->add(&*nParam); // Todo fix tokenizer, will throw error soon
	templist->add(&*connectToken); // Todo fix tokenizer, will throw error soon
	shared_ptr<Token> temp = shared_ptr<Token>(paramlist->first); // Todo fix tokenizer, will throw error soon

	while (temp != nullptr) 
	{
		templist->add(&*temp); // Todo fix tokenizer, will throw error soon
		temp = shared_ptr<Token>(temp->next); // Todo fix tokenizer, will throw error soon
	}
	connectToken = make_shared<Token>();
	connectToken->setEnum(Token::NEWLINE);
	connectToken->setLevel(nParam->getLevel());
	connectToken->setPositie(-1);
	connectToken->setPositieInList(-1);
	connectToken->setRegelnummer(-1);
	connectToken->setText("\n");
	templist->add(&*connectToken); // Todo fix tokenizer, will throw error soon
	
	temp = shared_ptr<Token>(templist->first); // Todo fix tokenizer, will throw error soon
	paramlist = make_shared<LinkedList>();

	while (temp != nullptr) 
	{
		paramlist->add(&*temp); // Todo fix tokenizer, will throw error soon
		temp = shared_ptr<Token>(temp->next); // Todo fix tokenizer, will throw error soon
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