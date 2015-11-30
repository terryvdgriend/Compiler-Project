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

	vm.addItemToVariableArrayAt(arrayKey, key, value);

	for (string & item : vm.getFunctionParametersByKey(parameters.at(1))) {
		vm.addItemToVariableArrayAt(item, key, value);
	}
}

pair<string, string> AddItemToArrayAtCommand::accept(CommandVisitor& commandVisitor) {
	return commandVisitor.visit(*this);
}