#include "stdafx.h"
#include "AddLengthToArrayCommand.h"
#include "CommandVisitor.h"

pair<string, string> AddLengthToArrayCommand::accept(CommandVisitor& commandVisitor) {
	return commandVisitor.visit(*this);
}

void AddLengthToArrayCommand::execute(VirtualMachine & vm, AbstractFunctionCall & node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();
	vm.setReturnValue(vm.getVariable(parameters[2])->getValue());
}
