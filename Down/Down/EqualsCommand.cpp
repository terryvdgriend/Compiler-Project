#include "stdafx.h"
#include "EqualsCommand.h"
#include "MandatoryCommandIncludes.h"

void EqualsCommand::execute(VirtualMachine& vm, vector<string>& parameters)
{
	Variable variable1 = *vm.getVariable(parameters.at(1));
	Variable variable2 = *vm.getVariable(parameters.at(2));

	variable1 = variable2;

    for(string & item : vm.getFunctionParametersByKey(parameters.at(1))) 
	{
        vm.setVariable(item, variable1.getValue());
    }
}

pair<string, string> EqualsCommand::accept(CommandVisitor& commandVisitor) 
{
	return commandVisitor.visit(*this);
}