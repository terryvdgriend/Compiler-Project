#include "stdafx.h"
#include "TimesCommand.h"
#include "CommandVisitor.h"

void TimesCommand::execute(VirtualMachine& vm, vector<string>& parameters)
{
	Variable variable1 = *vm.getVariable(parameters.at(1));
	Variable variable2 = *vm.getVariable(parameters.at(2));

	if (is_undefined(variable1, variable2, vm))
		return;

	if (variable1.getType() == VariableType::NUMBER && variable2.getType() == VariableType::NUMBER) {

		int number1 = atoi(variable1.getValue().c_str());
		int number2 = atoi(variable2.getValue().c_str());

		vm.setReturnValue(to_string(number1 * number2));
	}
	else {
		// Exception times heeft 2 nummers nodig
	}
}

std::pair<string, string> TimesCommand::accept(CommandVisitor& commandVisitor) {
	return commandVisitor.visit(*this);
}