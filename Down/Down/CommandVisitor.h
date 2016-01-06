#pragma once
#include "CommandVisitorList.h"

class CommandVisitor 
{
public: 
		// Array
	pair<string, string> visit(AddArrayToDictionaryCommand& command);
	pair<string, string> visit(AddItemToArrayAtCommand& command);
	pair<string, string> visit(AddLengthToArrayCommand& command);
		pair<string, string> visit(GetItemFromArrayCommand& command);

		// Functions
		pair<string, string> visit(ShowFunctionCommand& command);
		pair<string, string> visit(ShowUpFunctionCommand& command);
		pair<string, string> visit(RandomFunctionCommand& command);

		// Miscellaneous
	pair<string, string> visit(ConstantToReturnValueCommand& command);
		pair<string, string> visit(GetFromValueCommand& command);
		pair<string, string> visit(IdentifierToReturnValueCommand& command);

		// Operators
	pair<string, string> visit(DivideCommand& command);
	pair<string, string> visit(EqualsCommand& command);
	pair<string, string> visit(EqualsToCommand& command);
	pair<string, string> visit(GreaterEqualsToCommand& command);
	pair<string, string> visit(GreaterThanCommand& command);
	pair<string, string> visit(MinusCommand& command);
	pair<string, string> visit(MinusMinusCommand& command);
	pair<string, string> visit(ModuloCommand& command);
	pair<string, string> visit(NotEqualsToCommand& command);
	pair<string, string> visit(PlusCommand& command);
	pair<string, string> visit(PlusPlusCommand& command);
	pair<string, string> visit(SmallerEqualsToCommand& command);
	pair<string, string> visit(SmallerThanCommand& command);
	pair<string, string> visit(TimesCommand& command);
	pair<string, string> visit(CountCommand & command);
	pair<string, string> visit(GetAllFilesInDirectoryCommand & command);
	pair<string, string> visit(GetFilesInDirectoryByExtensionCommand & command);
	pair<string, string> visit(GetAudioFilesInDirectoryCommand & command);
	pair<string, string> visit(GetVideoFilesInDirectoryCommand & command);
	pair<string, string> visit(GetFileExtensionCommand & command);
	pair<string, string> visit(RenameFileCommand & command);
};