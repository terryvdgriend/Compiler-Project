#include "stdafx.h"
#include "CommandVisitor.h"

std::pair<string, string> CommandVisitor::visit(AddArrayToDictionaryCommand& command) {
	return std::pair<string, string>("", ""); // Change later
}
pair<string, string> CommandVisitor::visit(AddItemToArrayAtCommand& command) {
	return std::pair<string, string>("add item on position", "with type");
}
std::pair<string, string> CommandVisitor::visit(AddLengthToArrayCommand& command) {
	return std::pair<string, string>("", ""); // Change later
}
std::pair<string, string> CommandVisitor::visit(ConstantToReturnValueCommand& command) {
	return std::pair<string, string>("", "");
}
std::pair<string, string> CommandVisitor::visit(DivideCommand& command) { 
	return std::pair<string, string>("divide", "by");
}
std::pair<string, string> CommandVisitor::visit(EqualsCommand& command){
	return std::pair<string, string>("assign first variable", "with");
}
std::pair<string, string> CommandVisitor::visit(EqualsToCommand& command) {
	return std::pair<string, string>("compare (==)", "to");
}
std::pair<string, string> CommandVisitor::visit(GetFromValueCommand& command) {
	return std::pair<string, string>("", "");
}
std::pair<string, string> CommandVisitor::visit(GetItemFromArrayCommand& command) {
	return std::pair<string, string>("", ""); // Change later
}
std::pair<string, string> CommandVisitor::visit(GreaterEqualsToCommand& command) {
	return std::pair<string, string>("compare (>=)", "to");
}
std::pair<string, string> CommandVisitor::visit(GreaterThanCommand& command) {
	return std::pair<string, string>("compare (>)", "to");
}
std::pair<string, string> CommandVisitor::visit(IdentifierToReturnValueCommand& command) {
	return std::pair<string, string>("", "");
}
std::pair<string, string> CommandVisitor::visit(MinusCommand& command) {
	return std::pair<string, string>("subtract", "from");
}
std::pair<string, string> CommandVisitor::visit(MinusMinusCommand& command) {
	return std::pair<string, string>("subtract", "from");
}
std::pair<string, string> CommandVisitor::visit(ModuloCommand& command) {
	return std::pair<string, string>("get remainder (modulo)", "from");
}
std::pair<string, string> CommandVisitor::visit(NotEqualsToCommand& command) {
	return std::pair<string, string>("compare (!=)", "to");
}
std::pair<string, string> CommandVisitor::visit(PlusCommand& command) {
	return std::pair<string, string>("add", "to");
}
std::pair<string, string> CommandVisitor::visit(PlusPlusCommand& command) {
	return std::pair<string, string>("add", "to");
}
std::pair<string, string> CommandVisitor::visit(ShowFunctionCommand& command) {
	return std::pair<string, string>("", "");
}
std::pair<string, string> CommandVisitor::visit(SmallerEqualsToCommand& command) {
	return std::pair<string, string>("compare (<=)", "to");
}
std::pair<string, string> CommandVisitor::visit(SmallerThanCommand& command) {
	return std::pair<string, string>("compare (<)", "to");
}
std::pair<string, string> CommandVisitor::visit(TimesCommand& command) {
	return std::pair<string, string>("multiply", "by");
}