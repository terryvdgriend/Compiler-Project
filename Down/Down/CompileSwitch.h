#pragma once
#include "Compiler.h"
#include "SwitchNode.hpp"
class CompileSwitch:
	public Compiler
{
private:
	LinkedActionList* _compiledStatement;
	SwitchNode<class T>* SwitchNode;
public:
	CompileSwitch();
	~CompileSwitch();
	void ConnectLists();
	void Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
	Compiler * Create() { return new CompileSwitch(); };
};

