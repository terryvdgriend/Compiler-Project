#pragma once
#include "stdafx.h"
#include "ConstantToReturnValueCommand.h"

void ConstantToReturnValueCommand::execute(VirtualMachine& vm, vector<string>& parameters)
{
	vm.setReturnValue(parameters.at(1));
}