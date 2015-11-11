#pragma once

#include "ActionNode.h"
#include "VirtualMachine.h"
#include "SwitchNode.hpp"
class ConditionalJumpNode;
class DirectFunctionCall;
class DoNothingNode;
class FunctionCall;
class JumpGoToNode;

class NodeVisitor
{
	public:
		NodeVisitor(VirtualMachine& vm);
		~NodeVisitor();
		virtual void visit(ConditionalJumpNode& node);
		virtual void visit(DirectFunctionCall& node);
		virtual void visit(DoNothingNode& node);
		virtual void visit(FunctionCall& node);
		virtual void visit(JumpGoToNode& node);
		virtual void visit(SwitchNode<class T>& node);
		ActionNode* nextNode; // make private implement the below getters and setters
		//void getNextNode();
		//ActionNode* setNextNode();

	private:
		VirtualMachine* vm;
};