#include "stdafx.h"
#include "AddLengthToArrayCommand.h"

void AddLengthToArrayCommand::execute(VirtualMachine& vm, vector<string>& parameters)
{
	vm.setReturnValue(vm.getVariable(parameters[2])->getValue());	
}