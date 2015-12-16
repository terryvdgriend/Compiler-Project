#include "stdafx.h"
#include "EqualsCommand.h"
#include "MandatoryCommandIncludes.h"

void EqualsCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();

	shared_ptr<Variable> variable1 = vm.getVariable(parameters.at(1));
	shared_ptr<Variable> variable2 = vm.getVariable(parameters.at(2));

	if (variable1->getTokenType() == variable2->getTokenType()) 
	{

		variable1 = variable2;

		for (string& item : vm.getFunctionParametersByKey(parameters.at(1))) 
		{
			vm.setVariable(item, variable1->getValue(), variable1->getTokenType());
		}
	}
	else 
	{
		throwTypeError(*variable1, *variable2, vm);
	}
}

pair<string, string> EqualsCommand::accept(CommandVisitor& commandVisitor) 
{
	return commandVisitor.visit(*this);
}