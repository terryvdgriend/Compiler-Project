#pragma once
#include "Compiler.h"
#include "Token.h"

class CompileFactory
{
	public:
		CompileFactory();
		Compiler* createCompileStatement(Token& tknzr);

	private:
		map<Token::iToken, shared_ptr<Compiler>> mappert;
};