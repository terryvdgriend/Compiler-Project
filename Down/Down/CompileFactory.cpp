#include "stdafx.h"
#include "CompileFactory.h"
#include "CompilerHeader.h"

CompileFactory::CompileFactory()
{
	mappert[Token::IF] = new CompileIf();
	mappert[Token::WHILE] = new CompileWhile();
	mappert[Token::DO] = new CompileDoWhile();
	mappert[Token::FUNCTION] = new CompileFunction();
	mappert[Token::IDENTIFIER] = new CompileEquals();
}

Compiler * CompileFactory::CreateCompileStatement(const Token::iToken tknzr)
{
	std::map<Token::iToken, Compiler*>::iterator it = mappert.find(tknzr);
	if (it != mappert.end())
		return it->second->Create(); // Create is een copy maken
	return NULL;
}


CompileFactory::~CompileFactory()
{
}
