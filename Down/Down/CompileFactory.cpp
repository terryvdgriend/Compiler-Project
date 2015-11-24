#include "stdafx.h"
#include "CompileFactory.h"
#include "CompilerHeader.h"

CompileFactory::CompileFactory()
{
	mappert[Token::IF] = new CompileIf();
	mappert[Token::WHILE] = new CompileWhile();
	mappert[Token::FOR] = new CompileFor();
	mappert[Token::DO] = new CompileDoWhile();
	mappert[Token::FUNCTION_DECLARE_OPEN] = new CompileFunction();
	mappert[Token::IDENTIFIER] = new CompileEquals();
	mappert[Token::NEWLINE] = nullptr;
}

Compiler * CompileFactory::CreateCompileStatement(Token& tknzr)
{
	std::map<Token::iToken, Compiler*>::iterator it = mappert.find(tknzr.getEnum());
	if (it != mappert.end()){
		if (it->second != nullptr){
			return it->second->Create(); // Create is een copy maken
		}
		return nullptr;
	}
		
	//
	ErrorHandler::getInstance()->addError("Incorrect syntax ", &tknzr);

	return nullptr;
}


CompileFactory::~CompileFactory()
{
}
