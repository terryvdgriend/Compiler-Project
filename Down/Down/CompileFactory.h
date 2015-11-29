#pragma once
#include "Compiler.h"
#include "Token.h"

class CompileFactory
{
	public:
		CompileFactory();
		shared_ptr<Compiler> createCompileStatement(Token& tknzr);

	private:
		map<Token::iToken, shared_ptr<Compiler>> mappert;
};