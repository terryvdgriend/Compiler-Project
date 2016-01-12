#include "stdafx.h"
#include "RemoveFilesCommand.h"
#include "MandatoryCommandIncludes.h"

#ifdef _WIN32
#include "dirent.h"
#else
#include <dirent.h>
#endif

RemoveFilesCommand::RemoveFilesCommand()
{
}


RemoveFilesCommand::~RemoveFilesCommand()
{
}

void RemoveFilesCommand::execute(VirtualMachine & vm, AbstractFunctionCall & node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();
	auto varArray = vm.getVariableArray(parameters.at(1));
	auto variable1 = vm.getVariable(parameters[1]);
	vector<string> errors;
	if (variable1 != nullptr) {
		if (variable1->getTokenType() == IToken::TYPE_TEXT_ARRAY) {
			if (varArray != nullptr && varArray->variableArrayDictionary.size() > 0) {
				for (auto fileInArray : varArray->variableArrayDictionary) {
					string file = fileInArray->getValue();
					file.erase(remove(file.begin(), file.end(), '\"'), file.end());

					if (opendir(file.c_str()) != nullptr) {
						errors.push_back("File not found: " + file);
					}
					int result = remove(file.c_str());
					if (result != 0) {
						char buff[256];

						#ifdef _WIN32
								strerror_s(buff, 100, errno);
						#else
								strerror_r(100, buff, errno);
						#endif

						errors.push_back("Error: " + file + ": " + buff);
					}
				}
				for (auto err : errors) {
					throwCustomError(err, vm);
				}
				return;
			}
			throwCustomError("Array is empty.", vm);
			return;
		}
		throwCustomError("Parameters must be of type text.", vm);
		return;
	}
	throwCustomError("Can't find ", vm);
}

pair<string, string> RemoveFilesCommand::accept(CommandVisitor & cmdVisitor)
{
	return cmdVisitor.visit(*this);
}