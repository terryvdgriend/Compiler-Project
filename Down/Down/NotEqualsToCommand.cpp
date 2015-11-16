#include "stdafx.h"
#include "NotEqualsToCommand.h"
#include "CommandVisitor.h"

void NotEqualsToCommand::execute(VirtualMachine& vm, vector<string>& parameters)
{
	Variable variable1 = *vm.getVariable(parameters.at(1));
	Variable variable2 = *vm.getVariable(parameters.at(2));

	if (variable1.getValue() != variable2.getValue())
	{
		vm.setReturnValue("true");
	}
	else
	{
		vm.setReturnValue("false");
	}
}

std::pair<string, string> NotEqualsToCommand::accept(CommandVisitor& commandVisitor) {
	return commandVisitor.visit(*this);
}