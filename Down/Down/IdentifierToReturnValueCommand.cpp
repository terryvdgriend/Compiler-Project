#include "stdafx.h"
#include "IdentifierToReturnValueCommand.h"
#include "MandatoryCommandIncludes.h"

void IdentifierToReturnValueCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();

	vm.setReturnValue(parameters.at(1));
	vm.setReturnToken(node.getToken()->getSubType());
	vm.addIdentifer(parameters.at(1));
}

pair<string, string> IdentifierToReturnValueCommand::accept(CommandVisitor& commandVisitor) 
{
	return commandVisitor.visit(*this);
}