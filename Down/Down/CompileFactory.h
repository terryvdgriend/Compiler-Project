#pragma once
#include "Compiler.h"
#include "Token.h"

class CompileFactory
{
	public:
		CompileFactory();

		shared_ptr<Compiler> createCompileStatement(shared_ptr<Token>& token);

	private:
		map<Token::iToken, shared_ptr<Compiler>> tokenCompileDictionary;
};