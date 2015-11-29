#include "stdafx.h"
#include "Compute.h"
#include "Compiler.h"
#include "DoNothingNode.h"
#include "CompileFactory.h"

shared_ptr<LinkedActionList> Compute::computeCompile(LinkedList& tokenList)
{
	shared_ptr<LinkedActionList> compiledList = make_shared<LinkedActionList>();
	compiledList->add(new DoNothingNode());
	checkNewCompile(tokenList, *compiledList, shared_ptr<Token>(tokenList.first));	// Cleanup
	
	return compiledList;
}

void Compute::checkNewCompile(LinkedList& tokenList, LinkedActionList& compiledList, shared_ptr<Token> token)
{
	if (ErrorHandler::getInstance()->getErrors().size() > 0)
	{
		return;
	}

	if (token != nullptr)
	{
		unique_ptr<CompileFactory> fact = make_unique<CompileFactory>();
		unique_ptr<Compiler> compiler = fact->createCompileStatement(*token);

		if (compiler != nullptr)
		{
			compiledList.add(new DoNothingNode());
			compiler->compile(tokenList, *token, *tokenList.last, compiledList, *compiledList.getLast());
		}
		checkNewCompile(tokenList, compiledList, shared_ptr<Token>(token->next)); // Cleanup
	}
}