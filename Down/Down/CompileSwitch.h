#pragma once
#include "Compiler.h"
#include "SwitchNode.h"
class CompileSwitch:
	public Compiler
{
private:
	LinkedActionList* _compiledStatement;
	LinkedActionList* _condition;
	LinkedActionList* _bodyDefault;
	SwitchNode* _switchNode;
	std::map<LinkedActionList*, LinkedActionList*> _conditionBodyMap;
private:
	void CompileCase(LinkedList & cTokenList, Token & begin, Token & end);
public:
	CompileSwitch();
	void CompileDefault(LinkedList & cTokenList, Token & begin, Token & end);
	~CompileSwitch();
	void ConnectLists();
	void Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
	Compiler * Create() { return new CompileSwitch(); };
};

