#include "stdafx.h"
#include "CommandVisitor.h"
#include "MandatoryCommandVisitorIncludes.h"

pair<string, string> CommandVisitor::visit(AddArrayToDictionaryCommand& command) 
{
	return pair<string, string>("", "");
}

pair<string, string> CommandVisitor::visit(AddItemToArrayAtCommand& command) 
{
	return pair<string, string>("convert type", "to");
}

pair<string, string> CommandVisitor::visit(AddLengthToArrayCommand& command) 
{
	return pair<string, string>("", "");
}

pair<string, string> CommandVisitor::visit(GetItemFromArrayCommand& command)
{
	return pair<string, string>("", "");
}

pair<string, string> CommandVisitor::visit(ShowFunctionCommand& command)
{
	return pair<string, string>("", "");
}

pair<string, string> CommandVisitor::visit(ShowUpFunctionCommand& command)
{
	return pair<string, string>("", "");
}

pair<string, string> CommandVisitor::visit(RandomFunctionCommand& command)
{
	return pair<string, string>("", "");
}

pair<string, string> CommandVisitor::visit(ConstantToReturnValueCommand& command)
{
	return pair<string, string>("", "");
}

pair<string, string> CommandVisitor::visit(GetFromValueCommand& command)
{
	return pair<string, string>("", "");
}

pair<string, string> CommandVisitor::visit(IdentifierToReturnValueCommand& command)
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

pair<string, string> CommandVisitor::visit(GreaterEqualsToCommand& command) 
{
	return pair<string, string>("compare (>=)", "to");
}

pair<string, string> CommandVisitor::visit(GreaterThanCommand& command) 
{
	return pair<string, string>("compare (>)", "to");
}

pair<string, string> CommandVisitor::visit(MinusCommand& command) {
	return std::pair<string, string>("subtract", "by");
}

pair<string, string> CommandVisitor::visit(MinusMinusCommand& command) {
	return std::pair<string, string>("subtract", "by");
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
pair<string, string> CommandVisitor::visit(CountCommand& command) {
	return pair<string, string>("count array", "with");
}

pair<string, string> CommandVisitor::visit(GetAllFilesInDirectoryCommand& command) {
	return pair<string, string>("", "");
}

pair<string, string> CommandVisitor::visit(GetFilesInDirectoryByExtensionCommand & command)
{
	return pair<string, string>("", "");
}

pair<string, string> CommandVisitor::visit(GetAudioFilesInDirectoryCommand & command)
{
	return pair<string, string>("", "");
}

pair<string, string> CommandVisitor::visit(GetVideoFilesInDirectoryCommand & command)
{
	return pair<string, string>("", "");
}

pair<string, string> CommandVisitor::visit(RenameFileCommand & command)
{
	return pair<string, string>("", "");
}

pair<string, string> CommandVisitor::visit(RemoveFileCommand & command)
{
	return pair<string, string>();
}

pair<string, string> CommandVisitor::visit(RemoveFilesCommand & command)
{
	return pair<string, string>();
}

pair<string, string> CommandVisitor::visit(RemoveDirectoryCommand & command)
{
	return pair<string, string>();
}
pair<string, string> CommandVisitor::visit(MoveFileCommand & command)
{
	return pair<string, string>("","");
}

pair<string, string> CommandVisitor::visit(MoveFilesCommand & command)
{
	return pair<string, string>("", "");
}

pair<string, string> CommandVisitor::visit(CopyFileCommand & command)
{
	return pair<string, string>();
}

pair<string, string> CommandVisitor::visit(CopyFilesCommand & command)
{
	return pair<string, string>();
}

pair<string, string> CommandVisitor::visit(GetFileExtensionCommand& command) {
	return pair<string, string>("", "");
}

pair<string, string> CommandVisitor::visit(OrCommand & command)
{
	return pair<string, string>("", "");
}

pair<string, string> CommandVisitor::visit(AndCommand& command) {
	return pair<string, string>("", "");
}

pair<string, string> CommandVisitor::visit(GetDownCommand& command) {
	return pair<string, string>("", "");
}

pair<string, string> CommandVisitor::visit(ParseIntCommand& command) {
	return pair<string, string>("", "");
}

