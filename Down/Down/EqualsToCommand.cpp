#include "stdafx.h"
#include "EqualsToCommand.h"
#include "CommandVisitor.h"

void EqualsToCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();

	Variable variable1 = *vm.getVariable(parameters.at(1));
	Variable variable2 = *vm.getVariable(parameters.at(2));

	if (isUndefined(variable1, variable2, vm))
		return;

	if (variable1.getValue() == variable2.getValue())
	{
		vm.setReturnValue("true");
		vm.setReturnToken(Token::TYPE_FACT);
	}
	else
	{
		vm.setReturnValue("false");
		vm.setReturnToken(Token::TYPE_FACT);
	}
}

std::pair<string, string> EqualsToCommand::accept(CommandVisitor& commandVisitor) {
	return commandVisitor.visit(*this);
}