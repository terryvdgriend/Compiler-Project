#include "stdafx.h"
#include "CommandVisitor.h"
#include "CommandList.h"

pair<string, string> CommandVisitor::visit(ConstantToReturnValueCommand& command) 
{
	return pair<string, string>("", "");
}

pair<string, string> CommandVisitor::visit(DivideCommand& command) 
{ 
	return pair<string, string>("divide", "by");
}

pair<string, string> CommandVisitor::visit(EqualsCommand& command)
{
	return pair<string, string>("assign first variable", "with");
}

pair<string, string> CommandVisitor::visit(EqualsToCommand& command)
{
	return pair<string, string>("compare (==)", "to");
}

pair<string, string> CommandVisitor::visit(GetFromValueCommand& command)
{
	return pair<string, string>("", "");
}

pair<string, string> CommandVisitor::visit(GreaterEqualsToCommand& command)
{
	return pair<string, string>("compare (>=)", "to");
}

pair<string, string> CommandVisitor::visit(GreaterThanCommand& command)
{
	return pair<string, string>("compare (>)", "to");
}

pair<string, string> CommandVisitor::visit(IdentifierToReturnValueCommand& command)
{
	return pair<string, string>("", "");
}

pair<string, string> CommandVisitor::visit(MinusCommand& command)
{
	return pair<string, string>("subtract", "from");
}

pair<string, string> CommandVisitor::visit(MinusMinusCommand& command)
{
	return pair<string, string>("subtract", "from");
}

pair<string, string> CommandVisitor::visit(ModuloCommand& command)
{
	return pair<string, string>("get remainder (modulo)", "from");
}

pair<string, string> CommandVisitor::visit(NotEqualsToCommand& command)
{
	return pair<string, string>("compare (!=)", "to");
}

pair<string, string> CommandVisitor::visit(PlusCommand& command)
{
	return pair<string, string>("add", "to");
}

pair<string, string> CommandVisitor::visit(PlusPlusCommand& command)
{
	return pair<string, string>("add", "to");
}

pair<string, string> CommandVisitor::visit(ShowFunctionCommand& command)
{
	return pair<string, string>("", "");
}

pair<string, string> CommandVisitor::visit(SmallerEqualsToCommand& command)
{
	return pair<string, string>("compare (<=)", "to");
}

pair<string, string> CommandVisitor::visit(SmallerThanCommand& command)
{
	return pair<string, string>("compare (<)", "to");
}

pair<string, string> CommandVisitor::visit(TimesCommand& command)
{
	return pair<string, string>("multiply", "by");
}