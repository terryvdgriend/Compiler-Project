#include "stdafx.h"
#include "EqualsCommand.h"

void EqualsCommand::execute(VirtualMachine& vm, vector<string>& parameters)
{
	Variable variable1 = *vm.getVariable(parameters.at(1));
	Variable variable2 = *vm.getVariable(parameters.at(2));

	if (variable1.getValue() == "" && variable1.getType() == NULLTYPE)
	{
		variable1 = vm.getFunctionParameterValueByKey(parameters.at(1));
	}

	if (variable2.getValue() == "" && variable2.getType() == NULLTYPE)
	{
		variable2 = vm.getFunctionParameterValueByKey(parameters.at(2));

		Variable temp = variable1;
		variable1 = variable2;
		variable2 = temp;
	}
	
	variable1 = variable2;

    for(std::string & item : vm.getFunctionParametersByKey(parameters.at(1))) {
        vm.setVariable(item, variable1.getValue());
    }
}