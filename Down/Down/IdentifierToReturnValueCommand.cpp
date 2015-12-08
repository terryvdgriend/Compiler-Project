#include "stdafx.h"
#include "IdentifierToReturnValueCommand.h"
#include "CommandVisitor.h"

void IdentifierToReturnValueCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();
	vm.setReturnValue(parameters.at(1));
	vm.setReturnToken(node.getToken()->getSub());
	vm.addIdentifer(parameters.at(1));
}

std::pair<string, string> IdentifierToReturnValueCommand::accept(CommandVisitor& commandVisitor) {
	return commandVisitor.visit(*this);
}