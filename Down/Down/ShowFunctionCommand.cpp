#include "stdafx.h"
#include "ShowFunctionCommand.h"
#include <iostream>
#include <algorithm>
#include "CommandVisitor.h"

void ShowFunctionCommand::execute(VirtualMachine& vm, vector<string>& parameters)
{
	Variable variable2 = *vm.getVariable(parameters.at(2));
	string val = "";

	if (variable2.getType() != VariableType::NULLTYPE) {
		val += variable2.getValue();
	}

	val.erase(remove(val.begin(), val.end(), '\"'), val.end());
	cout << val << endl;
}

std::pair<string, string> ShowFunctionCommand::accept(CommandVisitor& commandVisitor) {
	return commandVisitor.visit(*this);
}