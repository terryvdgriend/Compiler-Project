#include "stdafx.h"
#include "CompileNextLevel.h"

CompileNextLevel::CompileNextLevel()
{
	_begin	= nullptr;
	_end	= nullptr;
	_before	= nullptr;
}

shared_ptr<Token> CompileNextLevel::getBegin()
{
	return _begin;
}

void CompileNextLevel::setBegin(shared_ptr<Token>& begin)
{
	_begin = begin;
}

shared_ptr<Token> CompileNextLevel::getEnd()
{
	return _end;
}

void CompileNextLevel::setEnd(shared_ptr<Token>& end)
{
	_end = end;
}

shared_ptr<ActionNode> CompileNextLevel::getBefore()
{
	return _before;
}

void CompileNextLevel::setBefore(shared_ptr<ActionNode>& before)
{
	_before = before;
}