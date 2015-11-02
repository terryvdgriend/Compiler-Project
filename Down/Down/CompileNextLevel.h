#pragma once

#include "Token.h"
#include "ActionNode.h"
class CompileNextLevel
{
public:
	CompileNextLevel();
	~CompileNextLevel();
	Token* begin;
	Token* end;
	ActionNode* before;
};