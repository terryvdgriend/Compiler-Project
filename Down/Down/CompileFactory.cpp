#include "stdafx.h"
#include "CompileFactory.h"
#include "CompilerHeader.h"

CompileFactory::CompileFactory()
{
	// Array
	tokenCompileDictionary.emplace(IToken::ARRAY_OPEN,				[]()-> shared_ptr<Compiler> { return make_shared<CompileArray>(); });

	// Coniditonal
	tokenCompileDictionary.emplace(IToken::IF,						[]()-> shared_ptr<Compiler> { return make_shared<CompileIf>(); });
	tokenCompileDictionary.emplace(IToken::SWITCH,					[]()-> shared_ptr<Compiler> { return make_shared<CompileSwitch>(); });

	// Function
	tokenCompileDictionary.emplace(IToken::FUNCTION_DECLARE_OPEN,	[]()-> shared_ptr<Compiler> { return make_shared<CompileGetFunction>(); });	// Existing function
	tokenCompileDictionary.emplace(IToken::FUNCTION_OPEN,			[]()-> shared_ptr<Compiler> { return make_shared<CompileUserFunction>(); });	// User defined functions

	// Loop
	tokenCompileDictionary.emplace(IToken::DO,						[]()-> shared_ptr<Compiler> { return make_shared<CompileDoWhile>(); });
	tokenCompileDictionary.emplace(IToken::FOR,						[]()-> shared_ptr<Compiler> { return make_shared<CompileFor>(); });
	tokenCompileDictionary.emplace(IToken::WHILE,					[]()-> shared_ptr<Compiler> { return make_shared<CompileWhile>(); });

	// Miscellaneous
	tokenCompileDictionary.emplace(IToken::IDENTIFIER,				[]()-> shared_ptr<Compiler> { return make_shared<CompileEquals>(); });
	tokenCompileDictionary.emplace(IToken::NEWLINE,					[]()-> shared_ptr<Compiler> { return nullptr; });
}

shared_ptr<Compiler> CompileFactory::createCompileStatement(shared_ptr<Token>& token)
{
	map<IToken, function<shared_ptr<Compiler>()>>::iterator it = tokenCompileDictionary.find(token->getType());

	if (it != tokenCompileDictionary.end())
	{
		if (it->second != nullptr)
		{
			if (token->getSubType() == IToken::TYPE_NUMBER_ARRAY || token->getSubType() == IToken::TYPE_TEXT_ARRAY || 
				token->getSubType() == IToken::TYPE_FACT_ARRAY)
			{
				if (token->getPrevious()->getType() == IToken::NEWLINE && token->getNext()->getType() == IToken::ARRAY_OPEN)
				{
					return make_shared<CompileAddArrayItem>();
				}
			}
			else 
			{
				return it->second();
			}
		}

		return nullptr;
	}
	ErrorHandler::getInstance()->addError("Incorrect syntax (CompileFactory): " + token->getText(), token);

	return nullptr;
}