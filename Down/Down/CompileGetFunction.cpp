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
	_bodyTokens			= make_shared<LinkedTokenList>();
	_compiledStatement	= make_shared<LinkedActionList>();
	_body				= make_shared<LinkedActionList>();
	_parameters			= make_shared<LinkedActionList>();
	_functionParams		= make_shared<LinkedActionList>();
	_functionCall		= make_shared<LinkedActionList>();
	_compiledStatement->add(make_shared<DoNothingNode>());
}

void CompileGetFunction::compile(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end,
								 shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore)
{
	shared_ptr<Token> current = begin;
	int level = begin->getLevel();

	list<shared_ptr<TokenExpectation>> expected;
	expected.push_back(make_shared<TokenExpectation>(level, IToken::FUNCTION_DECLARE_OPEN));
	expected.push_back(make_shared<TokenExpectation>(level, IToken::FUNCTION_CALL));

	for (shared_ptr<TokenExpectation> expectation : expected)
	{
		while (current->getType() == IToken::NEWLINE)
		{
			current = current->getNext();
		}

		if (expectation->getLevel() == level)
		{
			if (current->getType() == IToken::FUNCTION_CALL)
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

			if (current->getType() != expectation->getTokenType()) 
			{
				ErrorHandler::getInstance()->addError(make_shared<Error>("", ".md", current->getLevel(), current->getPosition(), ErrorType::error), 
													  expectation->getTokenType(), current->getType());
				begin = end;

				break;
			}
			else
			{
				current = current->getNext();
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

void CompileGetFunction::compileNotUserDefined(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end)
{
	shared_ptr<Token> current = begin;
	vector<string> parameters;
	_functionParams->add(make_shared<DoNothingNode>());

	while (current->getType() != IToken::FUNCTION_DECLARE_CLOSE)
	{
		// Compile condition
		shared_ptr<Token> seperator = current;
		stack<IToken> stack;

		while (stack.size() >= 0 && (seperator->getType() != IToken::AND_PARA || seperator->getType() != IToken::FUNCTION_DECLARE_CLOSE))
		{
			if (seperator->getType() == IToken::FUNCTION_DECLARE_OPEN)
			{
				stack.push(seperator->getType());
			}
			else if (seperator->getType() == IToken::FUNCTION_DECLARE_CLOSE && stack.size() > 0)
			{
				stack.pop();
			}
			else if (stack.size() == 0 && (seperator->getType() == IToken::AND_PARA || seperator->getType() == IToken::FUNCTION_DECLARE_CLOSE))
			{
				break;
			}
			seperator = seperator->getNext();
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

		if (current->getType() == IToken::AND_PARA)
		{
			current = current->getNext();
		}
	}

	if (parameters.size() > _params.size()) 
	{
		ErrorHandler::getInstance()->addError(make_shared<Error>(_name + " has more parameters than expected", ".md", current->getLineNumber(), 
											  current->getPosition(), ErrorType::error));
	}

	if (parameters.size() < _params.size()) 
	{
		ErrorHandler::getInstance()->addError(make_shared<Error>(_name + " has less parameters than expected", ".md", current->getLineNumber(), 
											 current->getPosition(), ErrorType::error));
	}
	shared_ptr<FunctionCall> pFunction = make_shared<FunctionCall>();
	pFunction->setArraySize(parameters.size()+1);
	pFunction->setAt(0, _name.c_str());

	for (int n = 0; (size_t)n < parameters.size(); n++)
	{
		pFunction->setAt(n + 1, parameters[n].c_str());
	}
	_functionCall->insertLast(pFunction);
	begin = current->getNext();
}

void CompileGetFunction::compileUserDefined(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end)
{
	CompileFactory factory;
	shared_ptr<Token> current = begin;
	shared_ptr<Token> last = end;
	vector<shared_ptr<LinkedTokenList>> paramList;
	int count = 0;

	if (_params.size() > 0) 
	{
		_parameters->add(make_shared<DoNothingNode>());
		shared_ptr<LinkedTokenList> param = make_shared<LinkedTokenList>();
		stack<IToken> stack;

		do 
		{
			if (current->getType() == IToken::FUNCTION_DECLARE_OPEN)
			{
				stack.push(current->getType());
			}
			else if (current->getType() == IToken::FUNCTION_DECLARE_CLOSE && stack.size() > 0)
			{
				stack.pop();
			}

			if ((size_t)count > _params.size() - 1)
			{
				ErrorHandler::getInstance()->addError(make_shared<Error>(_name + " has more parameters than expected", ".md", current->getLineNumber(), 
													  current->getPosition(), ErrorType::error));

				break;
			}

			if (stack.size() >= 0) 
			{
				if (stack.size() == 0 && current->getType() == IToken::AND_PARA)
				{
					if (param->getLast() != nullptr) 
					{
						param->getLast()->setNext(nullptr);
						param->getFirst()->setPrevious(nullptr);

						connectParams(_paramTokens.at(count), param);
						paramList.push_back(param);
					}
					else 
					{
						ErrorHandler::getInstance()->addError(make_shared<Error>(_name + " expected filling for the parameter", ".md", current->getLineNumber(), 
															  current->getPosition(), ErrorType::error));
					}
					param = make_shared<LinkedTokenList>();
					count++;
				}
				else 
				{
					param->add(make_shared<Token>(current));
				}
			}
			current = current->getNext();

			if (stack.size() == 0 && current->getType() == IToken::FUNCTION_DECLARE_CLOSE)
			{
				if (param->getLast() != nullptr) 
				{
					param->getLast()->setNext(nullptr);
					param->getFirst()->setPrevious(nullptr);
					connectParams(_paramTokens.at(count), param);
					paramList.push_back(param);
				}
				else 
				{
					ErrorHandler::getInstance()->addError(make_shared<Error>(_name + " expected filling for the parameter", ".md", current->getLineNumber(), 
														  current->getPosition(), ErrorType::error));
				}
				param = make_shared<LinkedTokenList>();

				break;
			}

		} 
		while (current != end);
	}

	if (paramList.size() < _params.size()) 
	{
		ErrorHandler::getInstance()->addError(make_shared<Error>(_name + " has less parameters than expected", ".md", current->getLineNumber(), 
											  current->getPosition(), ErrorType::error));
	}
	else if (paramList.size() > _params.size()) 
	{
		ErrorHandler::getInstance()->addError(make_shared<Error>(_name + " has more parameters than expected", ".md", current->getLineNumber(), 
											  current->getPosition(), ErrorType::error));
	}

	for (shared_ptr<LinkedTokenList> p : paramList)
	{
		shared_ptr<CompileEquals> condition = make_shared<CompileEquals>();
		condition->compile(p, p->getFirst(), p->getLast(), _parameters, _parameters->getLast());
	}

	if (_returnToken) 
	{
		_returnToken = make_shared<Token>(_returnToken);
		shared_ptr<LinkedActionList> rValue = make_shared<LinkedActionList>();
		shared_ptr<CompileCondition> con = make_shared<CompileCondition>();
		con->compile(tokenList, _returnToken, _returnToken, rValue, rValue->getLast());

		string sBuffer;
		shared_ptr<DirectFunctionCall> pDirectFunction = make_shared<DirectFunctionCall>(make_shared<Token>(_returnToken));
		string tempVar = getNextLocalVariableName(sBuffer);
		pDirectFunction->setArraySize(2);
		pDirectFunction->setAt(0, szGetFromReturnValue);
		pDirectFunction->setAt(1, tempVar.c_str());
		rValue->insertBefore(pDirectFunction, rValue->getLast());
		_body->add(rValue);
	}
	shared_ptr<LinkedTokenList> body = _bodyTokens;
	changeVariables(body);
	shared_ptr<Token> currentBody = body->getFirst();
	_body->add(make_shared<DoNothingNode>());

	while (currentBody != nullptr) 
	{
		if (currentBody->getType() == IToken::FUNCTION_CLOSE)
		{
			currentBody = currentBody->getNext();

			break;
		}
		shared_ptr<Compiler> compiledBodyPart = factory.createCompileStatement(currentBody);

		if (compiledBodyPart != nullptr) 
		{
			compiledBodyPart->compile(_bodyTokens, currentBody, body->getLast(), _body, _body->getLast());
		}
		else
		{
			currentBody = currentBody->getNext();
		}
	}

	if (_returnToken) 
	{
		string sBuffer;
		string tempVar = getNextLocalVariableName(sBuffer);
		changeVariable(_returnToken);
		shared_ptr<DirectFunctionCall> directFunctionCall = make_shared<DirectFunctionCall>(make_shared<Token>(_returnToken));
		directFunctionCall->setArraySize(2);
		directFunctionCall->setAt(0, SET_ID_TO_RT);
		directFunctionCall->setAt(1, _returnToken->getText().c_str());
		_body->insertBefore(_body->getLast(), directFunctionCall);
	}
	begin = current;
}

void CompileGetFunction::changeVariables(const shared_ptr<LinkedTokenList>& list)
{
	shared_ptr<Token> current = list->getFirst();

	while (current != nullptr) 
	{
		changeVariable(current);
		current = current->getNext();
	}
}

void CompileGetFunction::changeVariable(shared_ptr<Token>& token)
{
	string sBuffer;

	if (token->getType() == IToken::IDENTIFIER)
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

void CompileGetFunction::connectParams(shared_ptr<Token> param, shared_ptr<LinkedTokenList>& paramlist)
{
	shared_ptr<Token> connectToken = make_shared<Token>();
	shared_ptr<Token> nParam = make_shared<Token>(param);
	changeVariable(nParam);
	connectToken->setType(IToken::EQUALS);
	connectToken->setLevel(nParam->getLevel());
	connectToken->setPosition(-1);
	connectToken->setPositionInList(-1);
	connectToken->setLineNumber(-1);
	connectToken->setText("=");
	shared_ptr<LinkedTokenList> templist = make_shared<LinkedTokenList>();
	templist->add(nParam);
	templist->add(connectToken);
	shared_ptr<Token> temp = paramlist->getFirst();

	while (temp != nullptr) 
	{
		templist->add(temp);
		temp = temp->getNext();
	}
	connectToken = make_shared<Token>();
	connectToken->setType(IToken::NEWLINE);
	connectToken->setLevel(nParam->getLevel());
	connectToken->setPosition(-1);
	connectToken->setPositionInList(-1);
	connectToken->setLineNumber(-1);
	connectToken->setText("\n");
	templist->add(connectToken);
	
	temp = templist->getFirst();
	paramlist = make_shared<LinkedTokenList>();

	while (temp != nullptr) 
	{
		paramlist->add(temp);
		temp = temp->getNext();
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