#pragma once
#include "Compiler.h"
#include "Token.h"
#include <map>

class CompileFactory
{
private:
	std::map<Token::iToken,Compiler*> mappert;
public:
	CompileFactory();
	
	Compiler * CreateCompileStatement(const Token::iToken tknzr);

	~CompileFactory();
};

