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

void CompileNextLevel::setBegin(shared_ptr<Token>& value)
{
	begin = value;
}

shared_ptr<Token> CompileNextLevel::getEnd()
{
	return end;
}

void CompileNextLevel::setEnd(shared_ptr<Token>& value)
{
	end = value;
}

shared_ptr<ActionNode> CompileNextLevel::getBefore()
{
	return before;
}

void CompileNextLevel::setBefore(shared_ptr<ActionNode>& value)
{
	before = value;
}