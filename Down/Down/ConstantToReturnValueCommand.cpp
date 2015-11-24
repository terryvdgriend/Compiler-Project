#pragma once
#include "stdafx.h"
#include "ConstantToReturnValueCommand.h"
#include "CommandVisitor.h"

void ConstantToReturnValueCommand::execute(VirtualMachine& vm, vector<string>& parameters)
{
	vm.setReturnValue(parameters.at(1));
}

std::pair<string, string> ConstantToReturnValueCommand::accept(CommandVisitor& commandVisitor) {
	return commandVisitor.visit(*this);
}
