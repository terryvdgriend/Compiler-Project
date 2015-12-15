#pragma once
#include "Compiler.h"
#include "SwitchNode.h"

class CompileSwitch : public Compiler
{
	public:
		CompileSwitch();

		void compile(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end,
					 shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore);

	private:
		shared_ptr<LinkedActionList> _compiledStatement;
		shared_ptr<LinkedActionList> _condition;
		shared_ptr<LinkedActionList> _bodyDefault;
		shared_ptr<SwitchNode> _switchNode;
		map<shared_ptr<LinkedActionList>, shared_ptr<LinkedActionList>> _conditionBodyMap;

		void compileCase(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end);
		void compileDefault(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end);
		void connectLists();
};