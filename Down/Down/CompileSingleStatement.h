#pragma once
#include "Compiler.h"
#include "DirectFunctionCall.h"

class CompileSingleStatement : public Compiler
{
private:
	static const std::string SET_ID_TO_RT;
	static const std::string SET_CONST_TO_RT;
	static const std::string SET_GET_FROM_RT;
public:
	CompileSingleStatement();
	virtual void Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList listActionNodes, ActionNode actionBefore);
	~CompileSingleStatement();
};

