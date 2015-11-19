#include "stdafx.h"
#include "EqualsToCommand.h"
#include "CommandVisitor.h"

void EqualsToCommand::execute(VirtualMachine& vm, vector<string>& parameters)
{
	Variable variable1 = *vm.getVariable(parameters.at(1));
	Variable variable2 = *vm.getVariable(parameters.at(2));

	if (isUndefined(variable1, variable2, vm))
		return;

	if (variable1.getValue() == variable2.getValue())
	{
		vm.setReturnValue("true");
	}
	else
	{
		vm.setReturnValue("false");
	}
}

std::pair<string, string> EqualsToCommand::accept(CommandVisitor& commandVisitor) {
	return commandVisitor.visit(*this);
}