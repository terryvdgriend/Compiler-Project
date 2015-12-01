#include "stdafx.h"
#include "CompileOperator.h"
#include "FunctionCall.h"
#include "DirectFunctionCall.h"

#define szGetFromReturnValue "getFromReturnValue"

CompileOperator::CompileOperator(shared_ptr<Compiler> pNextLevel)
{
	this->pNextLevel = pNextLevel;
}

void CompileOperator::compile(LinkedList& tokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& before)
{
	unique_ptr<map<Token::iToken, string>::iterator> iFind;
	shared_ptr<Token> current = make_shared<Token>(begin);
	shared_ptr<vector<shared_ptr<ActionNode>>> beforeArray = make_shared<vector<shared_ptr<ActionNode>>>();
	shared_ptr<CompileNextLevel> nextLevel;
	shared_ptr<CompileNextLevelList> nextLevelList = nullptr;

	nextLevel.begin = &begin;

	while (current != nullptr && *current != end)
	{
		if (current->getEnum() == Token::NEWLINE)
		{
			break;
		}

		if (current->getPartner() != nullptr)
		{
			current = current->getPartner();
		}
		iFind = make_unique<map<Token::iToken, string>::iterator>(tokenMap.find(current->getEnum()));

		if (*iFind != tokenMap.end())
		{
			fillRunList(iFind->second, listActionNodes, before, &beforeArray);
			fillNextLevelList(&beforeArray, *current, nextLevel, nextLevelList);
		}
		current = current->next;
	}
	insertLastNextLevel(end, before, nextLevel, nextLevelList);
	compileNextLevel(tokenList, listActionNodes, nextLevelList);
	begin = *current;
}

void CompileOperator::fillRunList(const string& sFunctionName, LinkedActionList& listActionNodes, ActionNode& iBefore, vector<ActionNode*>* beforeList)
{
	string saArguments[3];
	string sBuffer;
	FunctionCall* pFunction = nullptr;
	DirectFunctionCall* pDirectFunction = nullptr;
	int maxN = 2;

	saArguments[0] = sFunctionName;
	saArguments[1] = getNextLocalVariableName(sBuffer);
	saArguments[2] = getNextLocalVariableName(sBuffer);

	for (int n = 0; n<maxN; n++)
	{
		pDirectFunction = new DirectFunctionCall;
		pDirectFunction->setArraySize(2);
		pDirectFunction->setAt(0, szGetFromReturnValue);
		pDirectFunction->setAt(1, saArguments[n + 1].c_str());
		beforeList->push_back(listActionNodes.insertBefore(&iBefore, pDirectFunction));
	}
	pFunction = new FunctionCall;
	pFunction->setArraySize(3);

	for (int n = 0; n < 3; n++)
	{
		pFunction->setAt(n, saArguments[n].c_str());
	}
	listActionNodes.insertBefore(&iBefore, pFunction);
}

void CompileOperator::fillNextLevelList(vector<ActionNode*>* beforeArray, Token& current, CompileNextLevel& nextLevel, CompileNextLevelList& nextLevelList)
{
	if (nextLevelList.size() == 0)
	{
		nextLevel.before = beforeArray->at(0);
	}
	nextLevel.end = &current;

	nextLevelList.push_back(nextLevel);

	nextLevel.before = beforeArray->at(1);
	nextLevel.begin = current.next;
}

void CompileOperator::insertLastNextLevel(Token& end, ActionNode& before, CompileNextLevel& nextLevel, CompileNextLevelList& nextLevelList)
{
	if (nextLevelList.size() == 0)
	{
		nextLevel.before = &before;
	}
	nextLevel.end = &end;

	nextLevelList.push_back(nextLevel);
}

void CompileOperator::compileNextLevel(LinkedList& tokenList, LinkedActionList& runList, CompileNextLevelList& nextLevelList)
{
	CompileNextLevelList::iterator  step = nextLevelList.begin();

	while (step != nextLevelList.end())
	{
		CompileNextLevel& nextLevelList = *step;

		pNextLevel->Compile(tokenList, *nextLevelList.begin, *nextLevelList.end, runList, *nextLevelList.before);
		++step;
	}
}

CompileOperator::TokenMap& CompileOperator::getTokenMap()
{
	return tokenMap;
}