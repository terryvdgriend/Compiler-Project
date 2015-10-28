#pragma once
#include "stdafx.h"
#include "EqualsToCommand.h"
#include "VariableType.h"
#include <string>
#include <cstddef>

EqualsToCommand::~EqualsToCommand()
{
	//Todo
}

bool String2Int(const std::string& str, int& result)
{
	result = std::atoi(str.c_str());
	return true;
}

void EqualsToCommand::execute(VirtualMachine *vm, vector<string> *parameters)
{
	Variable variable1 = vm->getVariable(parameters->at(1));
	Variable variable2 = vm->getVariable(parameters->at(2));

	if (variable1.getType() == VariableType::NUMBER || variable2.getType() == VariableType::NUMBER) {
		int val1;
		String2Int(variable1.getValue(), val1);
		int val2;
		String2Int(variable2.getValue(), val2);

		if (val1 == val2) {
			vm->setReturnValue("true");
		}
		else {
			vm->setReturnValue("false");
		}
	}
	else {
		if (variable1.getValue() == variable2.getValue()) {
			vm->setReturnValue("true");
		}
		else {
			vm->setReturnValue("false");
		}
	}

}