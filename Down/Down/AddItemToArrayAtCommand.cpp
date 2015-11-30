#include "stdafx.h"
#include "AddItemToArrayAtCommand.h"
#include "CommandVisitor.h"

void AddItemToArrayAtCommand::execute(VirtualMachine& vm, vector<string>& parameters)
{
	// Add item to array
	// Parameters:
	// 1. Array name
	// 2. Array location
	// 3. Item value

	// TODO: Errorhandling erbij maken

	string key = vm.getVariable(parameters[2]).get()->getValue();
	string value = vm.getVariable(parameters[3]).get()->getValue();
	string arrayKey = vm.getFunctionParametersByKey(parameters[1]).back();

	if (key != "" && value != "" && arrayKey != "")
	{
		vm.addItemToVariableArrayAt(arrayKey, key, value);

		for (string & item : vm.getFunctionParametersByKey(parameters.at(1))) {
			vm.addItemToVariableArrayAt(item, key, value);
		}
	}
	else
	{
		if (key == "")
		{
			ErrorHandler::getInstance()->addError(Error{ "you want to add an item to an array, but the key is empty", ".md", -1, -1, Error::error });
		}
		else if (value == "")
		{
			ErrorHandler::getInstance()->addError(Error{ "you want to add an item to an array, but the value is empty", ".md", -1, -1, Error::error });
		}
		else if (arrayKey == "")
		{
			ErrorHandler::getInstance()->addError(Error{ "you want to add an item to an array, but the array is undefined", ".md", -1, -1, Error::error });
		}
	}
}

pair<string, string> AddItemToArrayAtCommand::accept(CommandVisitor& commandVisitor) {
	return commandVisitor.visit(*this);
}