#include "stdafx.h"
#include "PlusCommand.h"

void PlusCommand::execute(VirtualMachine& vm, vector<string>& parameters)
{
	Variable variable1 = *vm.getVariable(parameters.at(1));
	Variable variable2 = *vm.getVariable(parameters.at(2));

	if (variable1.getType() == VariableType::NUMBER && variable2.getType() == VariableType::NUMBER) {

		int number1 = atoi(variable1.getValue().c_str());
		int number2 = atoi(variable2.getValue().c_str());

		vm.setReturnValue(to_string(number1 - number2));
	}
	else if (variable1.getType() == VariableType::NULLTYPE || variable2.getType() == VariableType::NULLTYPE) {
		// Exception 1 van de variabelen is null
	}
	else if (variable1.getType() == VariableType::BOOL || variable2.getType() == VariableType::BOOL) {
		// Exception plus werkt niet met bool
	}
	else {
		vm.setReturnValue(variable1.getValue() + variable2.getValue());
	}
}