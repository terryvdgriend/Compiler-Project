#pragma once
#include "ActionNode.h"
#include "VirtualMachine.h"
#include "SwitchNode.h"

class ConditionalJumpNode;
class DirectFunctionCall;
class DoNothingNode;
class FunctionCall;
class JumpGoToNode;
class SwitchNode;

class NodeVisitor
{
	public:
		NodeVisitor(VirtualMachine& virtualMachine);

		virtual void visit(ConditionalJumpNode& node);
		virtual void visit(DirectFunctionCall& node);
		virtual void visit(DoNothingNode& node);
		virtual void visit(FunctionCall& node);
		virtual void visit(JumpGoToNode& node);
		virtual void visit(SwitchNode& node);

	private:
		unique_ptr<VirtualMachine> vm;
		shared_ptr<ActionNode> nextNode;
};