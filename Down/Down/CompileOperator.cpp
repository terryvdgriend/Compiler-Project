#include "stdafx.h"
#include "CompileOperator.h"
#include "CompileEquals.h"
#include "FunctionCall.h"
#include "DirectFunctionCall.h"

#define szGetFromReturnValue "getFromReturnValue"

CompileOperator::CompileOperator(shared_ptr<Compiler> nextlevel)
{
	pNextLevel = nextlevel;
}

void CompileOperator::compile(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end,
							  shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore)
{
	int i = 2;
	int derp = i = i + 3;
	shared_ptr<Token> current = begin;
	map<IToken, string>::iterator iFind;
	vector<shared_ptr<ActionNode>> beforeArray;
	CompileNextLevel nextLevel;
	CompileNextLevelList nextLevelList;

	nextLevel.setBegin(begin);

	while (current != nullptr && *current != *end)
	{
		if (current->getType() == IToken::NEWLINE)
		{
			break;
		}

		if (current->getPartner() != nullptr)
		{
			current = current->getPartner();

			if (current == end)
			{
				break;
			}
		}
		iFind = tokenMap.find(current->getType());

		if (iFind != tokenMap.end())
		{
			fillRunList(iFind->second, listActionNodes, actionBefore, beforeArray, current);
			fillNextLevelList(beforeArray, current, nextLevel, nextLevelList);
			while (current != nullptr  && *current != *end) {
				if (current->getType() == IToken::NEWLINE)
				{
					break;
				}
				current = current->getNext();
			}
			break;
		}
		current = current->getNext();
	}
	insertLastNextLevel(end, actionBefore, nextLevel, nextLevelList);
	compileNextLevel(tokenList, listActionNodes, nextLevelList);
	begin = current;
}

void CompileOperator::fillRunList(const string& sFunctionName, shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& iBefore, 
								  vector<shared_ptr<ActionNode>>& beforeArray, shared_ptr<Token>& token)
{
	string saArguments[3];
	string sBuffer;
	int maxN = 2;

	saArguments[0] = sFunctionName;
	saArguments[1] = getNextLocalVariableName(sBuffer);
	saArguments[2] = getNextLocalVariableName(sBuffer);

	for (int n = 0; n < maxN; n++)
	{
        auto tempToken = make_shared<Token>(token);
		shared_ptr<DirectFunctionCall> pDirectFunction = make_shared<DirectFunctionCall>(tempToken);
		pDirectFunction->setArraySize(2);
		pDirectFunction->setAt(0, szGetFromReturnValue);
		pDirectFunction->setAt(1, saArguments[n + 1].c_str());
		beforeArray.push_back(listActionNodes->insertBefore(iBefore, pDirectFunction));
	}
	shared_ptr<FunctionCall> pFunction = make_shared<FunctionCall>();
	pFunction->setArraySize(3);

	for (int n = 0; n < 3; n++)
	{
		pFunction->setAt(n, saArguments[n].c_str());
	}
	listActionNodes->insertBefore(iBefore, pFunction);
}

void CompileOperator::fillNextLevelList(vector<shared_ptr<ActionNode>>& beforeArray, shared_ptr<Token>& current, CompileNextLevel& nextLevel, 
										CompileNextLevelList& nextLevelList)
{
	if (nextLevelList.size() == 0)
	{
		nextLevel.setBefore(beforeArray.at(0));
	}
	nextLevel.setEnd(current);

	nextLevelList.push_back(nextLevel);

	nextLevel.setBefore(beforeArray.at(1));
    auto next = current->getNext();
	nextLevel.setBegin(next);
}

void CompileOperator::insertLastNextLevel(shared_ptr<Token>& end, shared_ptr<ActionNode>& before, CompileNextLevel& nextLevel, 
										  CompileNextLevelList& nextLevelList)
{
	if (nextLevelList.size() == 0)
	{
		nextLevel.setBefore(before);
	}
	nextLevel.setEnd(end);
	nextLevelList.push_back(nextLevel);
}

void CompileOperator::compileNextLevel(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<LinkedActionList>& listActionNodes,
									   CompileNextLevelList& nextLevelList)
{
	CompileNextLevelList::iterator step = nextLevelList.begin();

	while (step != nextLevelList.end())
	{
		CompileNextLevel& nextLevelList = *step;
        auto fNode = nextLevelList.getBegin();
        auto eNode = nextLevelList.getEnd();
        auto eBefore = nextLevelList.getBefore();
		pNextLevel->compile(tokenList, fNode, eNode, listActionNodes, eBefore);
		++step;
		pNextLevel = make_shared<CompileEquals>();
	}
}