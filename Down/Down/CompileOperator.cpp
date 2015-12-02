#include "stdafx.h"
#include "CompileOperator.h"
#include "FunctionCall.h"
#include "DirectFunctionCall.h"

#define szGetFromReturnValue "getFromReturnValue"

CompileOperator::CompileOperator(shared_ptr<Compiler> pNextLevel)
{
	this->pNextLevel = pNextLevel;

	tokenMap = make_unique<map<Token::iToken, string>>();

}

void CompileOperator::compile(LinkedList& tokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& before)
{
	unique_ptr<map<Token::iToken, string>::iterator> iFind;
	shared_ptr<Token> current								= make_shared<Token>(begin);
	shared_ptr<vector<shared_ptr<ActionNode>>> beforeList	= make_shared<vector<shared_ptr<ActionNode>>>();
	shared_ptr<CompileNextLevel> nextLevel					= make_shared<CompileNextLevel>();
	CompileNextLevelList nextLevelList						= nullptr;

	nextLevel->setBegin(make_shared<Token>(begin));

	while (current != nullptr && *current != end)
	{
		if (current->getEnum() == Token::NEWLINE)
		{
			break;
		}

		if (current->getPartner() != nullptr)
		{
			current = shared_ptr<Token>(current->getPartner());  // Todo fix tokenizer, will throw error soon
		}
		iFind = make_unique<map<Token::iToken, string>::iterator>(tokenMap->find(current->getEnum()));

		if (*iFind != tokenMap->end())
		{
			fillRunList((*iFind)->second, listActionNodes, before, *beforeList);
			fillNextLevelList(*beforeList, *current, *nextLevel, nextLevelList);
		}
		current = shared_ptr<Token>(current->next); // Todo fix tokenizer, will throw error soon
	}
	insertLastNextLevel(end, before, *nextLevel, nextLevelList);
	compileNextLevel(tokenList, listActionNodes, nextLevelList);
	begin = *current;
}

void CompileOperator::fillRunList(const string& sFunctionName, LinkedActionList& listActionNodes, ActionNode& iBefore, vector<shared_ptr<ActionNode>>& beforeList)
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
		beforeList.push_back(listActionNodes.insertBefore(shared_ptr<ActionNode>(&iBefore), pDirectFunction));
	}
	pFunction = make_shared<FunctionCall>();
	pFunction->setArraySize(3);

	for (int n = 0; n < 3; n++)
	{
		pFunction->setAt(n, saArguments[n].c_str());
	}
	listActionNodes.insertBefore(shared_ptr<ActionNode>(&iBefore), pFunction);
}

void CompileOperator::fillNextLevelList(vector<shared_ptr<ActionNode>>& beforeArray, Token& current, CompileNextLevel& nextLevel, CompileNextLevelList& nextLevelList)
{
	if (nextLevelList->size() == 0)
	{
		nextLevel.setBefore(beforeArray.at(0));
	}
	nextLevel.setEnd(make_shared<Token>(current));

	nextLevelList->push_back(make_shared<CompileNextLevel>(nextLevel));

	nextLevel.setBefore(beforeArray.at(1));
	nextLevel.setBegin(shared_ptr<Token>(current.next)); // Todo fix tokenizer, will throw error soon
}

void CompileOperator::insertLastNextLevel(Token& end, ActionNode& before, CompileNextLevel& nextLevel, CompileNextLevelList& nextLevelList)
{
	if (nextLevelList->size() == 0)
	{
		nextLevel.setBefore(shared_ptr<ActionNode>(&before));
	}
	nextLevel.setEnd(make_shared<Token>(end));

	nextLevelList->push_back(make_shared<CompileNextLevel>(nextLevel));
}

void CompileOperator::compileNextLevel(LinkedList& tokenList, LinkedActionList& runList, CompileNextLevelList& nextLevelList)
{
	list<shared_ptr<CompileNextLevel>>::iterator step = nextLevelList->begin();

	while (step != nextLevelList->end())
	{
		shared_ptr<CompileNextLevel> nextLevelList =*step;
		pNextLevel->compile(tokenList, *nextLevelList->getBegin(), *nextLevelList->getEnd(), runList, *nextLevelList->getBefore());
		++step;
	}
}