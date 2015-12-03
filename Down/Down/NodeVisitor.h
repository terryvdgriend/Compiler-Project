#pragma once
#include "VirtualMachine.h"

class ActionNode;

class ConditionalJumpNode;
class DirectFunctionCall;
class DoNothingNode;
class FunctionCall;
class JumpGoToNode;
class SwitchNode;

class NodeVisitor
{
	public:
		NodeVisitor(shared_ptr<VirtualMachine>& virtualMachine);

		void visit(ConditionalJumpNode& node);
		void visit(DirectFunctionCall& node);
		void visit(DoNothingNode& node);
		void visit(FunctionCall& node);
		void visit(JumpGoToNode& node);
		void visit(SwitchNode& node);

		shared_ptr<ActionNode> getNextNode();

	private:
		shared_ptr<VirtualMachine> vm;
		shared_ptr<ActionNode> nextNode;
};