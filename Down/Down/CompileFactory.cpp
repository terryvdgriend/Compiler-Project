#include "stdafx.h"
#include "CompileFactory.h"
#include "CompilerHeader.h"

CompileFactory::CompileFactory()
{
	// Coniditonal
	tokenCompileDictionary[IToken::IF]						= make_shared<CompileIf>();
	tokenCompileDictionary[IToken::SWITCH]					= make_shared<CompileSwitch>();

	// Function
	tokenCompileDictionary[IToken::FUNCTION_DECLARE_OPEN]	= make_shared<CompileGetFunction>();	// Existing function
	tokenCompileDictionary[IToken::FUNCTION_OPEN]			= make_shared<CompileUserFunction>();	// User defined functions

	// Loop
	tokenCompileDictionary[IToken::DO]						= make_shared<CompileDoWhile>();
	tokenCompileDictionary[IToken::FOR]						= make_shared<CompileFor>();
	tokenCompileDictionary[IToken::WHILE]					= make_shared<CompileWhile>();

	// Miscellaneous
	tokenCompileDictionary[IToken::IDENTIFIER]				= make_shared<CompileEquals>();
	tokenCompileDictionary[IToken::NEWLINE]					= nullptr;
}

shared_ptr<Compiler> CompileFactory::createCompileStatement(shared_ptr<Token>& token)
{
	map<IToken, shared_ptr<Compiler>>::iterator it = tokenCompileDictionary.find(token->getType());

	if (it != tokenCompileDictionary.end())
	{
		if (it->second != nullptr)
		{
			return it->second->create(); // Create a copy
		}

		return nullptr;
	}
	ErrorHandler::getInstance()->addError("Incorrect syntax (CompileFactory): " + token->getText(), token);

	return nullptr;
}