#include "stdafx.h"
#include "CompileOperator.h"
#include "FunctionCall.h"
#include "DirectFunctionCall.h"

#define szGetFromReturnValue "getFromReturnValue"

CompileOperator::CompileOperator(shared_ptr<Compiler> pNextLevel)
{
	this->pNextLevel = pNextLevel;
}

void CompileOperator::compile(shared_ptr<LinkedList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end,
							  shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore)
{
	map<Token::iToken, string>::iterator iFind;
	shared_ptr<Token> current = begin;
	vector<shared_ptr<ActionNode>> beforeList;
	shared_ptr<CompileNextLevel> nextLevel = make_shared<CompileNextLevel>();
	CompileNextLevelList nextLevelList;

	nextLevel->setBegin(begin);

	while (current != nullptr && current != end)
	{
		if (current->getEnum() == Token::NEWLINE)
		{
			break;
		}
		iFind = tokenMap.find(current->getEnum());

		if (iFind != tokenMap.end())
		{
			fillRunList(iFind->second, listActionNodes, actionBefore, beforeList);
			fillNextLevelList(beforeList, current, nextLevel, nextLevelList);
		}
		current = shared_ptr<Token>(current->next); // Todo fix tokenizer, will throw error soon
	}
	insertLastNextLevel(end, actionBefore, nextLevel, nextLevelList);
	compileNextLevel(tokenList, listActionNodes, nextLevelList);
	begin = current;
}

void CompileOperator::fillRunList(const string& sFunctionName, shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& iBefore, 
								  vector<shared_ptr<ActionNode>>& beforeList)
{
	string saArguments[3];
	string sBuffer;
	shared_ptr<FunctionCall> pFunction = nullptr;
	shared_ptr<DirectFunctionCall> pDirectFunction = nullptr;
	int maxN = 2;

	saArguments[0] = sFunctionName;
	saArguments[1] = getNextLocalVariableName(sBuffer);
	saArguments[2] = getNextLocalVariableName(sBuffer);

	for (int n = 0; n<maxN; n++)
	{
		pDirectFunction = make_shared<DirectFunctionCall>();
		pDirectFunction->setArraySize(2);
		pDirectFunction->setAt(0, szGetFromReturnValue);
		pDirectFunction->setAt(1, saArguments[n + 1].c_str());
		beforeList.push_back(listActionNodes->insertBefore(iBefore, pDirectFunction));
	}
	pFunction = make_shared<FunctionCall>();
	pFunction->setArraySize(3);

	for (int n = 0; n < 3; n++)
	{
		pFunction->setAt(n, saArguments[n].c_str());
	}
	listActionNodes->insertBefore(iBefore, pFunction);
}

void CompileOperator::fillNextLevelList(vector<shared_ptr<ActionNode>>& beforeArray, shared_ptr<Token>& current, shared_ptr<CompileNextLevel>& nextLevel, 
										CompileNextLevelList& nextLevelList)
{
	if (nextLevelList.size() == 0)
	{
		nextLevel->setBefore(beforeArray.at(0));
	}
	nextLevel->setEnd(current);

	nextLevelList.push_back(nextLevel);

	nextLevel->setBefore(beforeArray.at(1));
	nextLevel->setBegin(shared_ptr<Token>(current->next)); // Todo fix tokenizer, will throw error soon
}

void CompileOperator::insertLastNextLevel(shared_ptr<Token>& end, shared_ptr<ActionNode>& before, shared_ptr<CompileNextLevel>& nextLevel, 
										  CompileNextLevelList& nextLevelList)
{
	if (nextLevelList.size() == 0)
	{
		nextLevel->setBefore(before);
	}
	nextLevel->setEnd(end);

	nextLevelList.push_back(nextLevel);
}

void CompileOperator::compileNextLevel(shared_ptr<LinkedList>& tokenList, shared_ptr<LinkedActionList>& listActionNodes, 
									   CompileNextLevelList& nextLevelList)
{
	list<shared_ptr<CompileNextLevel>>::iterator step = nextLevelList.begin();

	while (step != nextLevelList.end())
	{
		shared_ptr<CompileNextLevel> nextLevelList = *step;
		pNextLevel->compile(tokenList, nextLevelList->getBegin(), nextLevelList->getEnd(), listActionNodes, nextLevelList->getBefore());
		++step;
	}
}