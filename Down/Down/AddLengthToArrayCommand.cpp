#include "stdafx.h"
#include "AddLengthToArrayCommand.h"
#include "CommandVisitor.h"

void AddLengthToArrayCommand::execute(VirtualMachine& vm, vector<string>& parameters)
{
	vm.setReturnValue(vm.getVariable(parameters[2])->getValue());	
}

pair<string, string> AddLengthToArrayCommand::accept(CommandVisitor& commandVisitor) {
	return commandVisitor.visit(*this);
}