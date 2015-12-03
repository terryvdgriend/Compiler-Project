#include "stdafx.h"
#include "CompileFactory.h"
#include "CompilerHeader.h"

CompileFactory::CompileFactory()
{
	tokenCompileDictionary[Token::IF]						= make_shared<CompileIf>();
	tokenCompileDictionary[Token::WHILE]					= make_shared<CompileWhile>();
	tokenCompileDictionary[Token::FOR]						= make_shared<CompileFor>();
	tokenCompileDictionary[Token::DO]						= make_shared<CompileDoWhile>();
	tokenCompileDictionary[Token::FUNCTION_DECLARE_OPEN]	= make_shared<CompileGetFunction>();	// Existing function
	tokenCompileDictionary[Token::FUNCTION_OPEN]			= make_shared<CompileUserFunction>();	// User defined functions
	tokenCompileDictionary[Token::IDENTIFIER]				= make_shared<CompileEquals>();
	tokenCompileDictionary[Token::SWITCH]					= make_shared<CompileSwitch>();
	tokenCompileDictionary[Token::NEWLINE]					= nullptr;
}

shared_ptr<Compiler> CompileFactory::createCompileStatement(shared_ptr<Token>& token)
{
	map<Token::iToken, shared_ptr<Compiler>>::iterator it = tokenCompileDictionary.find(token->getEnum());

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