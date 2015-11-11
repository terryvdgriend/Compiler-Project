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
		template <typename T>
		void visit(SwitchNode<T>& node,T value){
			LinkedActionList* it = node.jumpMap.find(value);
			if (it != node.end()){
				nextNode = it->getFirst();
			}
			else{
				nextNode = node.defaultNodeList->getFirst();
			}
		}
		ActionNode* nextNode; // make private implement the below getters and setters
		//void getNextNode();
		//ActionNode* setNextNode();

	private:
		VirtualMachine* vm;
};