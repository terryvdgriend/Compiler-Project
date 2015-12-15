#pragma once
#include "Compiler.h"
#include "Token.h"
#include <map>
#include <functional>
class CompileFactory
{
private:
	std::map<Token::iToken, function<Compiler*()>> mappert;
public:
	CompileFactory();
	
	Compiler * CreateCompileStatement(Token& tknzr);

	~CompileFactory();
};

