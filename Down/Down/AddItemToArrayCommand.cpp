#include "stdafx.h"
#include "AddItemToArrayCommand.h"
#include "CommandVisitor.h"

void AddItemToArrayCommand::execute(VirtualMachine& vm, vector<string>& parameters)
{
	vector<Variable> varArray = vm.getVariableArray(parameters.at(1));
	Variable var = *vm.getVariable(parameters.at(2));

	vm.addItemToVariableArray(parameters.at(1), var);
}

pair<string, string> AddItemToArrayCommand::accept(CommandVisitor& commandVisitor) {
	return commandVisitor.visit(*this);
}