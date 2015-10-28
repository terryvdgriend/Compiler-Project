#pragma once
#include "stdafx.h"
#include "EqualsCommand.h"

void EqualsCommand::execute(VirtualMachine& vm, vector<string>& parameters)
{
	Variable variable1 = vm.getVariable(parameters.at(1));
	Variable variable2 = vm.getVariable(parameters.at(2));
}