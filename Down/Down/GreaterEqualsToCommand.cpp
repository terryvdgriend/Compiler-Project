#include "stdafx.h"
#include "GreaterEqualsToCommand.h"
#include "CommandVisitor.h"

void GreaterEqualsToCommand::execute(VirtualMachine& vm, vector<string>& parameters)
{
	Variable variable1 = *vm.getVariable(parameters.at(1));
	Variable variable2 = *vm.getVariable(parameters.at(2));

	if (isUndefined(variable1, variable2, vm))
		return;

	if (variable1.getType() == VariableType::NUMBER && variable2.getType() == VariableType::NUMBER) {
		int number1 = atoi(variable1.getValue().c_str());
		int number2 = atoi(variable2.getValue().c_str());
		if (number1 >= number2)
		{
			vm.setReturnValue("true");
		}
		else
		{
			vm.setReturnValue("false");
		}
	}
	else {
		// Exception "cannot compare different types than numbers"
		throwTypeError(variable1, variable2, vm);
		return;
	}
}

std::pair<string, string> GreaterEqualsToCommand::accept(CommandVisitor& commandVisitor) {
	return commandVisitor.visit(*this);
}