#include "stdafx.h"
#include "CompileGetFunction.h"
#include "DirectFunctionCall.h"
#include "FunctionCall.h"
#include "CompileFactory.h"

#define szGetFromReturnValue "getFromReturnValue"
#define SET_ID_TO_RT  "IdentifierToReturnValue"


CompileGetFunction::CompileGetFunction()
{
	_bodyTokens = new LinkedList();
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
						_paramTokens = p.getParamTokens();
						_bodyTokens = p.getBody();
						_returnToken = p.getReturn();
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
	LinkedActionList* list = &listActionNodes;
	list->insertBefore(&actionBefore, _compiledStatement);
	listActionNodes = *list;
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
		pDirectFunction = new DirectFunctionCall(*current);
		pDirectFunction->setArraySize(2);
		pDirectFunction->setAt(0, szGetFromReturnValue);
		pDirectFunction->setAt(1, tempVar.c_str());
		_functionParams->insertBefore(_functionParams->getLast(),pDirectFunction);
		///
		parameters.push_back(tempVar);
		if(current->getEnum() == Token::AND_PARA)
			current = current->next;
	}
	if (parameters.size() > _params.size()) {
		ErrorHandler::getInstance()->addError(Error{ _name +" has more parameters than expected", ".md", current->getLineNumber(),current->getPositie(), Error::error });
	}
	if (parameters.size()  < _params.size()) {
		ErrorHandler::getInstance()->addError(Error{ _name + " has less parameters than expected", ".md", current->getLineNumber(),current->getPositie(), Error::error });
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
	std::vector<LinkedList*> paramList;
	int count = 0;
	if (_params.size() > 0) {
		_parameters->add(new DoNothingNode());
		LinkedList* param = new LinkedList();
		do {
			if (count > _params.size()-1) {
				ErrorHandler::getInstance()->addError(Error{ _name + " has more parameters than expected", ".md", current->getLineNumber(),current->getPositie(), Error::error });
				break;
			}
			if (current->getEnum() != Token::AND_PARA)
				param->add(new Token(*current));
			else {
				param->last->next = nullptr;
				param->first->previous = nullptr;

				ConnectParams(_paramTokens.at(count), *param);
				paramList.push_back(param);
				param = new LinkedList();
				count++;
			}
			current = current->next;
			if (current->getEnum() == Token::FUNCTION_DECLARE_CLOSE) {
				param->last->next = nullptr;
				param->first->previous = nullptr;
				ConnectParams(_paramTokens.at(count), *param);
				paramList.push_back(param);
				param = new LinkedList();
				
			}

		} while (current->getEnum() != Token::FUNCTION_DECLARE_CLOSE);
	}
	if (count < _params.size() - 1) {
		ErrorHandler::getInstance()->addError(Error{ _name + " has less parameters than expected", ".md", current->getLineNumber(),current->getPositie(), Error::error });
	}

	for (auto p : paramList) {
		CompileEquals condition = CompileEquals();
		condition.Compile(*p, *p->first,*p->last,* _parameters, *_parameters->getLast());
	}
	if (_returnToken) {
		_returnToken = new Token(*_returnToken);
		LinkedActionList* rValue = new LinkedActionList();
		CompileCondition con = CompileCondition();
		con.Compile(cTokenList, *_returnToken, *_returnToken, *rValue, *rValue->getLast());

		std::string             sBuffer;
		DirectFunctionCall     *pDirectFunction = nullptr;
		std::string tempVar = getNextLocalVariableName(sBuffer);
		pDirectFunction = new DirectFunctionCall();
		pDirectFunction->setArraySize(2);
		pDirectFunction->setAt(0, szGetFromReturnValue);
		pDirectFunction->setAt(1, tempVar.c_str());
		rValue->insertBefore(pDirectFunction, rValue->getLast());
		_body->add(rValue);
	}
	LinkedList* body = new LinkedList(*_bodyTokens);
	ChangeVariables(*body);
	Token* currentBody = body->first;
	_body->add(new DoNothingNode());
	while (currentBody != nullptr) {
		if (currentBody->getEnum() == Token::FUNCTION_CLOSE) {
			currentBody = currentBody->next;
			break;
		}
		Compiler* compiledBodyPart = CompileFactory().CreateCompileStatement(*currentBody);

		if (compiledBodyPart != nullptr) {
			compiledBodyPart->Compile(*_bodyTokens, *currentBody, *body->last, *_body, *_body->getLast());
		}
		else
		{
			currentBody = currentBody->next;
		}
		delete compiledBodyPart;
	}

	if (_returnToken) {
		std::string             sBuffer;
		DirectFunctionCall     *pDirectFunction = nullptr;
		std::string tempVar = getNextLocalVariableName(sBuffer);
		ChangeVariable(*_returnToken);
		DirectFunctionCall *directFunctionCall = new DirectFunctionCall();
		directFunctionCall->setArraySize(2);
		directFunctionCall->setAt(0, SET_ID_TO_RT);
		directFunctionCall->setAt(1, _returnToken->getText().c_str());
		_body->insertBefore(_body->getLast(), directFunctionCall);
	}

	begin = *current;
	// dingen;
}

void CompileGetFunction::ChangeVariables(LinkedList& list) {
	Token* current = list.first;
	while (current != nullptr) {
		ChangeVariable(*current);
		current = current->next;
	}
}

void CompileGetFunction::ChangeVariable(Token & token) {
	std::string sBuffer;
	if (token.getEnum() == Token::IDENTIFIER) {
		std::string localVar;
		if (variableMap.count(token.getText()) > 0) {
			localVar = variableMap[token.getText()];
		}
		else {
			localVar = getNextLocalVariableName(sBuffer)+"_"+ token.getText();
			variableMap[token.getText()] = localVar;
		}
		token.setText(localVar);
	}	
}

void CompileGetFunction::ConnectParams(Token * param,LinkedList &paramlist)
{
	Token* connectToken = new Token();
	Token * nParam = new Token(*param);
	ChangeVariable(*nParam);
	connectToken->setEnum(Token::EQUALS);
	connectToken->setLevel(nParam->getLevel());
	connectToken->setPositie(-1);
	connectToken->setPositieInList(-1);
	connectToken->setRegelnummer(-1);
	connectToken->setText("=");
	LinkedList* templist = new LinkedList();
	templist->add(nParam);
	templist->add(connectToken);
	Token* temp = paramlist.first;
	while (temp != nullptr) {
		templist->add(temp);
		temp = temp->next;
	}
	connectToken = new Token();
	connectToken->setEnum(Token::NEWLINE);
	connectToken->setLevel(nParam->getLevel());
	connectToken->setPositie(-1);
	connectToken->setPositieInList(-1);
	connectToken->setRegelnummer(-1);
	connectToken->setText("\n");
	templist->add(connectToken);
	
	temp = templist->first;
	paramlist = *new LinkedList();
	while (temp != nullptr) {
		paramlist.add(temp);
		temp = temp->next;
	}
}

CompileGetFunction::~CompileGetFunction()
{
}
