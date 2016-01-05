#include "stdafx.h"
#include "AddLengthToArrayCommand.h"
#include "MandatoryCommandIncludes.h"

void AddLengthToArrayCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();
	if (parameters.size() == 4) {
		vm.setReturnValue((vm.getVariable(parameters.at(1))->getValue() + ";" + vm.getVariable(parameters.at(2))->getValue()));
	}
	else
		vm.setReturnValue(vm.getVariable(parameters[1])->getValue());
}

pair<string, string> AddLengthToArrayCommand::accept(CommandVisitor& commandVisitor) 
{
	return commandVisitor.visit(*this);
}