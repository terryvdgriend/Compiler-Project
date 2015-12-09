#include "stdafx.h"
#include "CompileFactory.h"
#include "CompilerHeader.h"

CompileFactory::CompileFactory()
{
	mappert.emplace(Token::IF, []() -> Compiler* { return new CompileIf; });
	mappert.emplace(Token::WHILE, []() -> Compiler* { return new CompileWhile; });
	mappert.emplace(Token::FOR, []() -> Compiler* { return new CompileFor; });
	mappert.emplace(Token::DO, []() -> Compiler* { return new CompileDoWhile; });
	mappert.emplace(Token::FUNCTION_DECLARE_OPEN, []() -> Compiler* { return new CompileGetFunction; });
	mappert.emplace(Token::FUNCTION_OPEN, []() -> Compiler* { return new CompileUserFunction; });
	mappert.emplace(Token::IDENTIFIER, []() -> Compiler* { return new CompileEquals; });
	mappert.emplace(Token::ARRAY_OPEN, []() -> Compiler* { return new CompileArray; });
	mappert.emplace(Token::SWITCH, []() -> Compiler* { return new CompileSwitch; });
	mappert.emplace(Token::NEWLINE, []() -> Compiler* { return nullptr; });
}

Compiler * CompileFactory::CreateCompileStatement(Token& tknzr)
{
	auto it = mappert.find(tknzr.getEnum());
	if (it != mappert.end()){
		if (it->second != nullptr) {
			if (tknzr.getSub() == Token::TYPE_NUMBER_ARRAY || tknzr.getSub() == Token::TYPE_TEXT_ARRAY || tknzr.getSub() == Token::TYPE_FACT_ARRAY)
			{
				if (tknzr.previous->getEnum() == Token::NEWLINE && tknzr.next->getEnum() == Token::ARRAY_OPEN) { 
					return new CompileAddArrayItem;
				}
			}
			else {
				return it->second();
			}

		}
		return nullptr;
	}
		
	//
	ErrorHandler::getInstance()->addError("Incorrect syntax (CompileFactory): " + tknzr.getText(), &tknzr);

	return nullptr;
}


CompileFactory::~CompileFactory()
{
}
