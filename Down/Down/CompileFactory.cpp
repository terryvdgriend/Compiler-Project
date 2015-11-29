#include "stdafx.h"
#include "CompileFactory.h"
#include "CompilerHeader.h"

CompileFactory::CompileFactory()
{
	mappert[Token::IF]						= make_shared<CompileIf>();
	mappert[Token::WHILE]					= make_shared<CompileWhile>();
	mappert[Token::FOR]						= make_shared<CompileFor>();
	mappert[Token::DO]						= make_shared<CompileDoWhile>();
	//mappert[Token::FUNCTION_DECLARE_OPEN]	= make_shared<CompileFunction>();		// Existing function
	mappert[Token::FUNCTION_DECLARE_OPEN]	= make_shared<CompileGetFunction>();	// Existing function
	mappert[Token::FUNCTION_OPEN]			= make_shared<CompileUserFunction>();	// User defined functions
	mappert[Token::IDENTIFIER]				= make_shared<CompileEquals>();
	mappert[Token::SWITCH]					= make_shared<CompileSwitch>();
	mappert[Token::NEWLINE]					= nullptr;
}

shared_ptr<Compiler> CompileFactory::createCompileStatement(Token& tknzr)
{
	map<Token::iToken, shared_ptr<Compiler>>::iterator it = mappert.find(tknzr.getEnum());

	if (it != mappert.end())
	{
		if (it->second != nullptr)
		{
			return it->second->create(); // Create a copy
		}

		return nullptr;
	}
	ErrorHandler::getInstance()->addError("Incorrect syntax (CompileFactory): " + tknzr.getText(), &tknzr);

	return nullptr;
}