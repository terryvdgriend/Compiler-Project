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
	
	return lRun;
}

void Compute::CheckNewCompile(LinkedList* lToken, LinkedActionList* lRun, Token* token){
	if (ErrorHandler::getInstance()->getErrors().size() > 0)
		return;
	if (token != nullptr){
		CompileFactory fact { CompileFactory() };

		Compiler* compiler = fact.CreateCompileStatement(*token);
		if (compiler != nullptr){
			lRun->add(new DoNothingNode());
			compiler->Compile(*lToken, *token, *lToken->last, *lRun, *lRun->getLast());
		}

		//Text::PrintLine("");

		//lRun->printList();

		//Text::PrintLine("");

		CheckNewCompile(lToken, lRun, token->next);
	}
}


Compute::~Compute()
{
}
