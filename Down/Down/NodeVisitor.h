#pragma once

class NodeVisitor
{
	public:
		virtual void visit(ConditionalJumpNode node) = 0;
		virtual void visit(DirectFunctionCall node) = 0;
		virtual void visit(DoNothingNode node) = 0;
		virtual void visit(FunctionCall node) = 0;
		virtual void visit(JumpGotoNode node) = 0;
};