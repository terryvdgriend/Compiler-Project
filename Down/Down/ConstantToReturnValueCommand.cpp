#pragma once
#include "stdafx.h"
#include "ConstantToReturnValueCommand.h"
#include "CommandVisitor.h"


void ConstantToReturnValueCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();
	vm.setReturnValue(parameters.at(1));
	vm.setReturnToken(node.getToken()->getSub());
}

std::pair<string, string> ConstantToReturnValueCommand::accept(CommandVisitor& commandVisitor) {
	return commandVisitor.visit(*this);
}
