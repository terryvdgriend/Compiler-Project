#include "stdafx.h"
#include "IdentifierToReturnValueCommand.h"
#include "CommandVisitor.h"

void IdentifierToReturnValueCommand::execute(VirtualMachine& vm, vector<string>& parameters)
{
	vm.setReturnValue(parameters.at(1));
	vm.addIdentifer(parameters.at(1));
}

std::pair<string, string> IdentifierToReturnValueCommand::accept(CommandVisitor& commandVisitor) {
	return commandVisitor.visit(*this);
}