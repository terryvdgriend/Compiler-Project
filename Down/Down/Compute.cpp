#include "stdafx.h"
#include "Compute.h"
#include "Compiler.h"
#include "DoNothingNode.h"
#include "CompileFactory.h"

shared_ptr<LinkedActionList> Compute::computeCompile(LinkedList& tokenList)
{
	shared_ptr<LinkedActionList> compiledList = make_shared<LinkedActionList>();
	compiledList->add(new DoNothingNode());
	checkNewCompile(tokenList, *compiledList, tokenList.first);
	
	return compiledList;
}

void Compute::checkNewCompile(LinkedList& tokenList, LinkedActionList& compiledList, shared_ptr<Token> token)
{
	if (token != nullptr)
	{
		unique_ptr<CompileFactory> fact = make_unique<CompileFactory>();
		unique_ptr<Compiler> compiler = fact->createCompileStatement(*token);

		if (compiler != nullptr)
		{
			compiledList.add(new DoNothingNode());
			compiler->Compile(tokenList, *token, *tokenList.last, compiledList, *compiledList.getLast());
		}
		checkNewCompile(tokenList, compiledList, token->next);
	}
}