#pragma once
#include "Compiler.h"
#include "SwitchNode.h"

class CompileSwitch : public Compiler
{
	public:
		CompileSwitch();

		void compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
		shared_ptr<Compiler> create();

	private:
		shared_ptr<LinkedActionList> _compiledStatement;
		shared_ptr<LinkedActionList> _condition;
		shared_ptr<LinkedActionList> _bodyDefault;
		shared_ptr<SwitchNode> _switchNode;
		shared_ptr<map<shared_ptr<LinkedActionList>, shared_ptr<LinkedActionList>>> _conditionBodyMap;

		void compileCase(LinkedList& cTokenList, Token& begin, Token& end);
		void compileDefault(LinkedList& cTokenList, Token& begin, Token& end);
		void connectLists();
};