#pragma once
#include "VirtualMachine.h"
#include "NodeVisitor.h"

class ConditionalJumpNode;
class DirectFunctionCall;
class DoNothingNode;
class FunctionCall;
class JumpGotoNode;

class NextNodeVisitor : public NodeVisitor
{
	public:
		NextNodeVisitor(VirtualMachine* vm);
		~NextNodeVisitor();
		void visit(ConditionalJumpNode& node);
		void visit(DirectFunctionCall& node);
		void visit(DoNothingNode& node);
		void visit(FunctionCall& node);
		void visit(JumpGotoNode& node);
		ActionNode* nextNode;
		//void getNextNode();
		//ActionNode* setNextNode();

	private:
		VirtualMachine* vm;
};