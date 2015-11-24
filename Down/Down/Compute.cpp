#include "stdafx.h"
#include "Compute.h"
#include "Compiler.h"
#include "DoNothingNode.h"
#include "CompileFactory.h"

Compute::Compute()
{
}

shared_ptr<LinkedActionList> Compute::computeCompile(LinkedList* lToken)
{
	shared_ptr<LinkedActionList> lRun = make_shared<LinkedActionList>();
	lRun->add(new DoNothingNode());
	checkNewCompile(lToken, lRun, lToken->first);
	
	return lRun;
}

void Compute::checkNewCompile(LinkedList* lToken, shared_ptr<LinkedActionList> lRun, Token* token)
{
	if (token != nullptr)
	{
		unique_ptr<CompileFactory> fact = make_unique<CompileFactory>();
		Compiler* compiler = fact.CreateCompileStatement(*token);

		if (compiler != nullptr)
		{
			lRun->add(new DoNothingNode());
			compiler->Compile(*lToken, *token, *lToken->last, *lRun, *lRun->getLast());
		}
		CheckNewCompile(lToken, lRun, token->next);
	}
}