#include "stdafx.h"
#include "ConstantToReturnValueCommand.h"
#include "MandatoryCommandIncludes.h"

void ConstantToReturnValueCommand::execute(VirtualMachine& vm, vector<string>& parameters)
{
	vm.setReturnValue(parameters.at(1));
}

pair<string, string> ConstantToReturnValueCommand::accept(CommandVisitor& commandVisitor) 
{
	return commandVisitor.visit(*this);
}