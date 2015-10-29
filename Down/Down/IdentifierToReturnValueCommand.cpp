#include "stdafx.h"
#include "IdentifierToReturnValueCommand.h"

void IdentifierToReturnValueCommand::execute(VirtualMachine& vm, vector<string>& parameters)
{
	vm.setReturnValue(parameters.at(1));
	vm.addIdentifer(parameters.at(1));
}