#include "stdafx.h"
#include "PlusCommand.h"
#include "CommandVisitor.h"

void PlusCommand::execute(VirtualMachine& vm, vector<string>& parameters)
{
	Variable variable1 = *vm.getVariable(parameters.at(1));
	Variable variable2 = *vm.getVariable(parameters.at(2));

	if (isUndefined(variable1, variable2, vm))
		return;

	if (variable1.getType() == VariableType::NUMBER && variable2.getType() == VariableType::NUMBER) {

		int number1 = atoi(variable1.getValue().c_str());
		int number2 = atoi(variable2.getValue().c_str());

		vm.setReturnValue(to_string(number1 + number2));
	}
	else {
		vm.setReturnValue(variable1.getValue() + variable2.getValue());
	}
}

std::pair<string, string> PlusCommand::accept(CommandVisitor& commandVisitor) {
	return commandVisitor.visit(*this);
}