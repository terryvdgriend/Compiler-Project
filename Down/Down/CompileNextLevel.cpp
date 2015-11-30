#include "stdafx.h"
#include "CompileNextLevel.h"

CompileNextLevel::CompileNextLevel()
{
	begin	= nullptr;
	end		= nullptr;
	before	= nullptr;
}

shared_ptr<Token> CompileNextLevel::getBegin()
{
	return begin;
}

shared_ptr<Token> CompileNextLevel::getEnd()
{
	return end;
}

shared_ptr<ActionNode> CompileNextLevel::getBefore()
{
	return before;
}