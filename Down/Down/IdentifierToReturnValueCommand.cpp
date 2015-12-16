#include "stdafx.h"
#include "IdentifierToReturnValueCommand.h"
#include "MandatoryCommandIncludes.h"

void IdentifierToReturnValueCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();
	vm.setReturnValue(parameters.at(1));
	vm.setReturnToken(node.getToken()->getSubType());
	vm.addIdentifer(parameters.at(1));

	vm.addArrayTypeToArrayTypes(node.getToken()->getText(), node.getToken()->getSubType());
}

pair<string, string> IdentifierToReturnValueCommand::accept(CommandVisitor& commandVisitor) 
{
	return commandVisitor.visit(*this);
}