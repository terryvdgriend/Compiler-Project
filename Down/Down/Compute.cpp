#include "stdafx.h"
#include "Compute.h"
#include "Compiler.h"
#include "CompileFactory.h"
#include "DoNothingNode.h"

shared_ptr<LinkedActionList> Compute::computeCompile(shared_ptr<LinkedList>& tokenList)
{
	shared_ptr<LinkedActionList> compiledList = make_shared<LinkedActionList>();
	compiledList->add(make_shared<DoNothingNode>());
	checkNewCompile(tokenList, compiledList, shared_ptr<Token>(tokenList->first)); // Will break when refactoring tokenizer (token in particular)
	
	return compiledList;
}

void Compute::checkNewCompile(shared_ptr<LinkedList>& tokenList, shared_ptr<LinkedActionList>& compiledList, shared_ptr<Token> token)
{
	if (ErrorHandler::getInstance()->getErrors().size() > 0)
	{
		return;
	}

	if (token != nullptr)
	{
		unique_ptr<CompileFactory> factory = make_unique<CompileFactory>();
		shared_ptr<Compiler> compiler = factory->createCompileStatement(token);

		if (compiler != nullptr)
		{
			compiledList->add(make_shared<DoNothingNode>());
			compiler->compile(tokenList, token, shared_ptr<Token>(tokenList->last), compiledList, compiledList->getLast()); // Will break when refactoring tokenizer (token in particular)
		}
		checkNewCompile(tokenList, compiledList, shared_ptr<Token>(token->next));
	}
}