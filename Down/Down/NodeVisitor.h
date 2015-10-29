#pragma once
#include "ConditionalJumpNode.h"
#include "DirectFunctionCall.h"
#include "DoNothingNode.h"
#include "FunctionCall.h"
#include "JumpGotoNode.h"

class ConditionalJumpNode;
class DirectFunctionCall;
class DoNothingNode;
class FunctionCall;
class JumpGotoNode;

class NodeVisitor
{
	public:
		virtual void visit(DoNothingNode node) = 0;
		virtual void visit(JumpGotoNode node) = 0;
		virtual void visit(ConditionalJumpNode node) = 0;
		virtual void visit(FunctionCall node) = 0;
		virtual void visit(DirectFunctionCall node) = 0;
};