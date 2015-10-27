#include "stdafx.h"
#include "CompileFactory.h"
#include "CompilePlusMinus.h"

CompileFactory::CompileFactory()
{
	mappert[Token::IF] = new CompileOperator();
}

Compiler * CompileFactory::CreateCompileStatement(const Token::iToken tknzr)
{
	Compiler * dieding = mappert.find(Token::IF)->second;
	//Compiler * aaa(NULL);
	//CompileEquals compily{};// = new CompileEquals();
	return dieding->Create();
}


CompileFactory::~CompileFactory()
{
}
