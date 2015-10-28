#pragma once
#include "stdafx.h"
#include "GreaterEqualsToCommand.h"

void GreaterEqualsToCommand::execute(VirtualMachine& vm, vector<string>& parameters)
{
	Variable variable1 = vm.getVariable(parameters.at(1));
	Variable variable2 = vm.getVariable(parameters.at(2));

	if (variable1.getType() == VariableType::NUMBER && variable2.getType() == VariableType::NUMBER) {
		if (variable1.getValue() >= variable2.getValue())
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
	}
}