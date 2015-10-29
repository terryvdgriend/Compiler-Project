#pragma once
#include "VirtualMachine.h"
#include "ConditionalJumpNode.h"
#include "DirectFunctionCall.h"
#include "DoNothingNode.h"
#include "FunctionCall.h"
#include "JumpGotoNode.h"

class NodeVisitor
{
	public:
		NodeVisitor(VirtualMachine& vm);
		~NodeVisitor();
		void visit(ConditionalJumpNode& node);
		void visit(DirectFunctionCall& node);
		void visit(DoNothingNode& node);
		void visit(FunctionCall& node);
		void visit(JumpGotoNode& node);
		ActionNode* nextNode; // make private implement the below getters and setters
		//void getNextNode();
		//ActionNode* setNextNode();

	private:
		VirtualMachine* vm;
};