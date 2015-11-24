#include "stdafx.h"
#include "CompileGetFunction.h"
#include "DirectFunctionCall.h"
#include "FunctionCall.h"

#define szGetFromReturnValue "getFromReturnValue"


CompileGetFunction::CompileGetFunction()
{
	_body = new LinkedActionList();
	_compiledStatement = new LinkedActionList();
	_compiledStatement->add(new DoNothingNode());
	_functionParams = new LinkedActionList();
	_functionCall = new LinkedActionList();
	_parameters = new LinkedActionList();
}

void CompileGetFunction::ConnectLists()
{
	
	if (userdef) {
		if (_parameters->Count() > 0)
			_compiledStatement->add(_parameters);
		_compiledStatement->add(_body);
	}
	else {
		_compiledStatement->add(_functionParams);
		_compiledStatement->add(_functionCall);
	}
}

void CompileGetFunction::Compile(LinkedList & cTokenList, Token & begin, Token & end, LinkedActionList & listActionNodes, ActionNode & actionBefore)
{
	Token* current = &begin;
	int Level = begin.getLevel();

	Token* bodyEnd = nullptr;
	//
	std::list<TokenExpectation> expected = std::list<TokenExpectation>();
	expected.push_back(TokenExpectation(Level, Token::FUNCTION_DECLARE_OPEN));
	expected.push_back(TokenExpectation(Level, Token::FUNCTION_CALL));
	for (TokenExpectation expectation : expected)
	{
		while (current->getEnum() == Token::NEWLINE) {
			current = current->next;
		}
		if (expectation.getLevel() == Level) {
			if (current->getEnum() == Token::FUNCTION_CALL) {
				for (auto p : FunctionHandler::getInstance()->getFunctions()) 
				{
					if (p.getName() == current->getText()) {
						_name = p.getName();
						_params = p.getParams();
						_body = p.getBody();
						userdef = p.isUserdef();
						break;
					}
				}
			}
			if (current->getEnum() != expectation.getTokenType()) {
				ErrorHandler::getInstance()->addError(Error{ "", ".md", current->getLevel(), current->getPositie(), Error::error }, expectation.getTokenType(), current->getEnum());
				begin = end;
				break;
			}
			else
				current = current->next;
		}
	}
	if (!userdef)
		CompileNotUserDefined(cTokenList, *current, end);
	else 
		CompileUserDefined(cTokenList, *current, end);


	ConnectLists();
	begin = *current;
	listActionNodes.add(_compiledStatement);
}

void CompileGetFunction::CompileNotUserDefined(LinkedList & cTokenList, Token & begin, Token & end)
{
	Token *current = &begin;
	std::vector<std::string> parameters;
	_functionParams->add(new DoNothingNode());
	while (current->getEnum() != Token::FUNCTION_DECLARE_CLOSE) {
		// compile condition
		Token * seperator = current;
		while (seperator->getEnum() != Token::AND_PARA || seperator->getEnum() != Token::FUNCTION_DECLARE_CLOSE) {
			if (seperator->getEnum() == Token::AND_PARA || seperator->getEnum() == Token::FUNCTION_DECLARE_CLOSE)
				break;
			seperator = seperator->next;
		}
		CompileCondition condition = CompileCondition();
		condition.Compile(cTokenList, *current, *seperator, *_functionParams, *_functionParams->getLast());
		/// create direct functioncall
		std::string             sBuffer;
		DirectFunctionCall     *pDirectFunction = nullptr;
		std::string tempVar = getNextLocalVariableName(sBuffer);
		pDirectFunction = new DirectFunctionCall();
		pDirectFunction->setArraySize(2);
		pDirectFunction->setAt(0, szGetFromReturnValue);
		pDirectFunction->setAt(1, tempVar.c_str());
		_functionParams->insertBefore(_functionParams->getLast(),pDirectFunction);
		///
		parameters.push_back(tempVar);
	}


	FunctionCall* pFunction = new FunctionCall();
	pFunction->setArraySize(parameters.size()+1);

	pFunction->setAt(0, _name.c_str());
	for (int n = 0; n < parameters.size(); n++)
		pFunction->setAt(n+1, parameters[n].c_str());

	_functionCall->insertLast(pFunction);
	begin = *current->next;
}

void CompileGetFunction::CompileUserDefined(LinkedList & cTokenList, Token & begin, Token & end)
{
	Token *current = &begin;
	std::vector<std::vector<Token*>> paramList;
	if (_params.size() > 0) {
		_parameters->add(new DoNothingNode());
		std::vector<Token*> param;
		while (current->getEnum() != Token::FUNCTION_DECLARE_CLOSE) {
			if (current->getEnum() != Token::AND_PARA)
				param.push_back(current);
			else {
				paramList.push_back(param);
				param = {};
			}
			current = current->next;
		}
		paramList.push_back(param);
	}

	for (auto p : paramList) {
		CompileCondition condition = CompileCondition();
		condition.Compile(cTokenList, *p.front(),* p.back(),* _parameters, *_parameters->getLast());
		std::string             sBuffer;
		DirectFunctionCall     *pDirectFunction = nullptr;
		std::string tempVar = getNextLocalVariableName(sBuffer);
		pDirectFunction = new DirectFunctionCall();
		pDirectFunction->setArraySize(2);
		pDirectFunction->setAt(0, szGetFromReturnValue);
		pDirectFunction->setAt(1, tempVar.c_str());
		_parameters->insertBefore(_parameters->getLast(), pDirectFunction);
	}



	begin = *current;
	// dingen;
}

CompileGetFunction::~CompileGetFunction()
{
}
