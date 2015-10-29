#include "stdafx.h"
#include "Compute.h"
#include "Compiler.h"
#include "DoNothingNode.h"
#include "CompileFactory.h"

Compute::Compute()
{
}

LinkedActionList* Compute::ComputeCompile(LinkedList* lToken, LinkedActionList* lRun){
	CheckNewCompile(lToken, lRun, lToken->first);
	_CrtDumpMemoryLeaks();
	return lRun;
}

void Compute::CheckNewCompile(LinkedList* lToken, LinkedActionList* lRun, Token* token){
	if (token != nullptr){
		CompileFactory fact { CompileFactory() };
		Compiler* compiler = fact.CreateCompileStatement(token->getEnum());
		if (compiler != nullptr){
			lRun->add(new DoNothingNode());
			compiler->Compile(*lToken, *token, *lToken->last, *lRun, *lRun->getLast());
		}
		CheckNewCompile(lToken, lRun, token->next);
	}
}


Compute::~Compute()
{
}
