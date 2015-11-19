#include "stdafx.h"
#include "GetItemFromArrayCommand.h"

void GetItemFromArrayCommand::execute(VirtualMachine& vm, vector<string>& parameters)
{
	vector<Variable> varArray = vm.getVariableArray(parameters.at(1));
	Variable* variable1 = vm.getVariable(parameters.at(2));

	vm.setReturnValue(varArray.at(atoi(variable1->getValue().c_str())).getValue());
}

