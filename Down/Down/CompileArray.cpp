#include "stdafx.h"
#include "CompileArray.h"
#include "CompileAddArrayItem.h"
#include "CompilerHeader.h"
#include "CompileSingleStatement.h"
#include "DirectFunctionCall.h"
#include "FunctionCall.h"
#include "TokenExpectation.h"

#define SET_ID_TO_RT "IdentifierToReturnValue"
#define SET_CONST_TO_RT "ConstantToReturnValue"
#define SET_GET_FROM_RT "getFromReturnValue"

void CompileArray::compile(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end,
						   shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore)
 {
	shared_ptr<Token> current = begin;
	int level = begin->getLevel();
	bool compiledArraySize = false;

	bool hasEquals = false;
	bool hasEqualsWithFunc = false;
	bool isMultiDimensional = false;
	shared_ptr<Token> identifier;
	shared_ptr<Token> seeker = current;

	isArrayLengthFilled = false;




	while (seeker->getType() != IToken::NEWLINE)
	{
		if (seeker->getType() == IToken::EQUALS)
		{
			if (seeker->getNext() != nullptr && seeker->getNext()->getType() == IToken::FUNCTION_DECLARE_OPEN)
				hasEqualsWithFunc = true;
			else
				hasEquals = true;

			break;
		}
		seeker = seeker->getNext();
	}

	list<TokenExpectation> expected = list<TokenExpectation>();
	expected.push_back(TokenExpectation(level, IToken::ARRAY_OPEN));
	expected.push_back(TokenExpectation(level + 1, IToken::ANY));
	expected.push_back(TokenExpectation(level, IToken::ARRAY_CLOSE));
	expected.push_back(TokenExpectation(level, IToken::IDENTIFIER));

	if (hasEquals)
	{
		expected.push_back(TokenExpectation(level, IToken::EQUALS));
		expected.push_back(TokenExpectation(level, IToken::ARRAY_OPEN));
		expected.push_back(TokenExpectation(level + 1, IToken::ANY));
		expected.push_back(TokenExpectation(level, IToken::ARRAY_CLOSE));
	}
	else if (hasEqualsWithFunc) {
		expected.push_back(TokenExpectation(level, IToken::EQUALS));
		expected.push_back(TokenExpectation(level, IToken::FUNCTION_DECLARE_OPEN));
		expected.push_back(TokenExpectation(level, IToken::FUNCTION_DECLARE_CLOSE));
	}

	int expecCount = 0;
	for (TokenExpectation expectation : expected)
	{
		expecCount++;
		while (current->getType() == IToken::NEWLINE)
		{
			if (current->getNext() != nullptr)
			{
				current = current->getNext();
			}
			else
			{
				break;
			}
		}

		if (current == nullptr)
		{
            auto error = make_shared<Error>("making array not completed", ".md", -1, -1, ErrorType::ERROR);
			ErrorHandler::getInstance()->addError(error);
			begin = end;

			break;
		}
		string sBuffer;

		if (expectation.getLevel() == level)
		{
			if (current->getType() != expectation.getTokenType())
			{
                auto error = make_shared<Error>("", ".md", current->getLineNumber(), current->getPosition(), ErrorType::ERROR);
				ErrorHandler::getInstance()->addError(error, expectation.getTokenType(), current->getType());
				begin = end;

				break;
			}
			
			else if (current->getType() == IToken::FUNCTION_DECLARE_OPEN && current->getType() == expectation.getTokenType()) {
				CompileEquals compiler;
                auto eNode = current->getPartner();
				compiler.compile(tokenList, identifier, eNode, listActionNodes, actionBefore);
                auto tempToken = make_shared<Token>(current);
				shared_ptr<DirectFunctionCall> directFunctionCall = make_shared<DirectFunctionCall>(tempToken);
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_GET_FROM_RT);
				directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
				listActionNodes->insertBefore(actionBefore, directFunctionCall);

				current = identifier;
			}

			else if (current->getType() == IToken::IDENTIFIER)
			{
				CompileSingleStatement compiledBodyPart;
                auto eNode = current->getNext();
                auto eBefore = listActionNodes->getLast();
                compiledBodyPart.compile(tokenList, current, eNode, listActionNodes, eBefore);
                auto tempToken = make_shared<Token>(current);
				shared_ptr<DirectFunctionCall> directFunctionCall = make_shared<DirectFunctionCall>(tempToken);
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_GET_FROM_RT);
				directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
				listActionNodes->insertBefore(actionBefore, directFunctionCall);

				vector<string> saArguments(2+multiParam.size());
				shared_ptr<FunctionCall> pFunction = make_shared<FunctionCall>();


				currentArrayTempVar = getCurrentLocalVariableName();
				saArguments[0] = "$AddLengthToArray";
				int count = 1;
				for (auto it : multiParam) {
					saArguments[count] = it;
					count++;
				}
				saArguments[count] = currentArrayTempVar;

				pFunction->setArraySize(saArguments.size());

				for (int n = 0; n < saArguments.size(); n++)
				{
					pFunction->setAt(n, saArguments[n].c_str());
				}
				listActionNodes->insertBefore(actionBefore, pFunction);

				isArrayLengthFilled = true;


				saArguments[0] = "$AddArrayToDictionary";
				saArguments[1] = currentArrayTempVar;

				pFunction = make_shared<FunctionCall>();
				pFunction->setArraySize(2);

				for (int n = 0; n < 2; n++)
				{
					pFunction->setAt(n, saArguments[n].c_str());
				}
				listActionNodes->insertBefore(actionBefore, pFunction);
				if (hasEqualsWithFunc) {
					identifier = current;
				}
				current = current->getNext();
			}
			else {
				current = current->getNext();
			}
			
		}
		else if (expectation.getLevel() >= level)
		{
			if (current->getType() == IToken::ARRAY_CLOSE || current->getNext()->getType() == IToken::NEWLINE) 
			{
                auto error = make_shared<Error>("", ".md", current->getLineNumber(), current->getPosition(), ErrorType::ERROR);
				ErrorHandler::getInstance()->addError(error,expectation.getTokenType(), IToken::NONE);
				begin = end;

				break;
			}


			int countOfRows = 0;
			executeArrayItems(listActionNodes, tokenList, actionBefore, current, sBuffer, countOfRows, isMultiDimensional);
			while (current->getType() != IToken::ARRAY_CLOSE)
			{
				current = current->getPrevious();
			}
			
		}
	}
	begin = current;
}

bool CompileArray::executeArrayItems(shared_ptr<LinkedActionList> &listActionNodes, shared_ptr<LinkedTokenList> tokenList, shared_ptr<ActionNode> &actionBefore, shared_ptr<Token> &current, string sBuffer, int countOfRows, bool isMultiDimensional)
{
	shared_ptr<Token> seeker = current;
	shared_ptr<Token> arrayClose;
	while (seeker)
	{
		if (arrayClose != nullptr && seeker->getType() == IToken::NEWLINE || arrayClose != nullptr &&  seeker->getType() == IToken::IDENTIFIER)
			break;
		if (seeker->getType() == IToken::ARRAY_OPEN)
			arrayClose = seeker;
			seeker = seeker->getPrevious();
	}
	arrayClose = arrayClose->getPartner();
	vector<shared_ptr<Param>> paramList;

	shared_ptr<Param> param = make_shared<Param>();
	stack<IToken> stack;

	vector<int> indexes(multiParam.size(),-1);
	do
	{
		if (current->getType() == IToken::ARRAY_OPEN || current->getType() == IToken::FUNCTION_DECLARE_OPEN)
		{
			if(current->getType() == IToken::ARRAY_OPEN)
				indexes[stack.size()]++;
			stack.push(current->getType());
		}
		else if ((current->getType() == IToken::ARRAY_CLOSE || current->getType() == IToken::FUNCTION_DECLARE_CLOSE) && stack.size() > 0)
		{
			if(current->getType() == IToken::ARRAY_CLOSE && current->getPrevious()->getType() == IToken::ARRAY_CLOSE)
				indexes[stack.size()] = -1;
			stack.pop();
		}

		if (stack.size() >= 0)
		{
			if (stack.size() >= 0 && current->getType() == IToken::AND_PARA && current->getPrevious()->getType() == IToken::ARRAY_CLOSE) {
			}
			else if (stack.size() >= 0 && current->getType() == IToken::ARRAY_CLOSE  && (current->getNext() !=nullptr && current->getNext()->getType() == IToken::AND_PARA )||stack.size() == 0 && current->getType() == IToken::AND_PARA || stack.size() > 0 && stack.top() == IToken::ARRAY_OPEN && (current->getType() == IToken::AND_PARA || current->getType() == IToken::ARRAY_CLOSE))
			{
				if (param->params->getLast() != nullptr)
				{
					//indexes[stack.size() - 1] = stack.size() - 1;
					if (multiParam.size() > 0) {
						if(current->getType() == IToken::ARRAY_CLOSE)
							indexes[stack.size()+1]++;
						else
							indexes[stack.size()]++;
						
						param->paramIndexes = indexes;
					}
					createNewLineToken(param, paramList);
				}
				else
				{
					auto error = make_shared<Error>("no assignment is array", ".md", current->getLineNumber(),current->getPosition(), ErrorType::ERROR);
					ErrorHandler::getInstance()->addError(error);
				}
				if (multiParam.size() > 0) 
					if (current->getType() == IToken::ARRAY_CLOSE)
						indexes[stack.size()+1] = -1;
				param = make_shared<Param>();
			}
			else
			{
				if(current->getType() != IToken::ARRAY_OPEN && current->getType() != IToken::ARRAY_CLOSE)
					param->params->add(make_shared<Token>(current));
			}
		}
		current = current->getNext();

		if (stack.size() == 0 && current->getType() == IToken::ARRAY_CLOSE)
		{
			if (multiParam.size() == 0) {
				if (param->params->getLast() != nullptr)
				{
					createNewLineToken(param, paramList);
				}
				else
				{
					auto error = make_shared<Error>("no assignment is array", ".md", current->getLineNumber(),current->getPosition(), ErrorType::ERROR);
					ErrorHandler::getInstance()->addError(error);
				}
				param = make_shared<Param>();
			}
			else if (isArrayLengthFilled && multiParam.size() == 1) {
				if (param->params->getLast() != nullptr)
				{
							indexes[stack.size()]++;

						param->paramIndexes = indexes;
					createNewLineToken(param, paramList);
				}
				else
				{
					auto error = make_shared<Error>("no assignment is array", ".md", current->getLineNumber(),current->getPosition(), ErrorType::ERROR);
					ErrorHandler::getInstance()->addError(error);
				}
				param = make_shared<Param>();
			}
			

			break;
		}
	} while (current != arrayClose);

	if (!isArrayLengthFilled)
	{
		for (int i = 0; i < paramList.size(); i++) {
			shared_ptr<Compiler> compileParam;
			if (paramList.at(i)->params->getSize() > 1) 
			{
				compileParam = make_shared<CompilePlusMinus>();
			}
			else
			{
				compileParam = make_shared<CompileSingleStatement>();
			}
			auto eFirst = paramList.at(i)->params->getFirst();
			auto eLast = paramList.at(i)->params->getLast();
			auto eBefore = actionBefore;
			compileParam->compile(tokenList, eFirst, eLast, listActionNodes, eBefore);
			auto tempToken = make_shared<Token>(current);
			shared_ptr<DirectFunctionCall> directFunctionCall = make_shared<DirectFunctionCall>(tempToken);
			string param = getNextLocalVariableName(sBuffer).c_str();
			multiParam.push_back(param);
			directFunctionCall->setArraySize(2);
			directFunctionCall->setAt(0, SET_GET_FROM_RT);
			directFunctionCall->setAt(1, param.c_str());
			listActionNodes->insertBefore(actionBefore, directFunctionCall);
		}
	}
	else
	{
		for (auto p : paramList)
		{

			CompileAddArrayItem compiledBodyPart;
			shared_ptr<ActionNode> lastActionNode = listActionNodes->getLast()->getPrevious();

			compiledBodyPart.setFromArray(true);
	
			compiledBodyPart.setFromMultiArrayLength(filledMultiLength);
			compiledBodyPart.setMultiArray(isMultiDimensional);
			compiledBodyPart.setItemPositionInMultiArray(p->paramIndexes);

			compiledBodyPart.setFromArrayLength(filledLength++);
			compiledBodyPart.setCurrentArray(currentArrayTempVar);

			auto fNode = p->params->getFirst();
			auto eNode = p->params->getLast();
			auto eBefore = listActionNodes->getLast();
			compiledBodyPart.compile(tokenList, fNode, eNode, listActionNodes, eBefore);

			if (current->getType() == IToken::AND_PARA)
			{
				current = current->getNext();
			}
		}
		if (isMultiDimensional && current->getType() == IToken::ARRAY_CLOSE && current->getNext()->getType() == IToken::ARRAY_CLOSE)
		{
			current = current->getNext();
		}
	}

	return false;
}

void CompileArray::createNewLineToken(shared_ptr<Param>& param, vector<shared_ptr<Param>>& list)
{
	param->params->getLast()->setNext(nullptr);
	param->params->getFirst()->setPrevious(nullptr);
	shared_ptr<Token> connectToken = make_shared<Token>();
	connectToken->setType(IToken::NEWLINE);
	connectToken->setLevel(param->params->getLast()->getLevel());
	connectToken->setPosition(param->params->getLast()->getPosition());
	connectToken->setPositionInList(param->params->getLast()->getPosition());
	connectToken->setLineNumber(param->params->getLast()->getLineNumber());
	connectToken->setText("\n");
	param->params->add(connectToken);
	list.push_back(param);
}