#include "stdafx.h"
#include "ModuloCommand.h"
#include "MandatoryCommandIncludes.h"

void ModuloCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();

	Variable variable1 = *vm.getVariable(parameters.at(1));
	Variable variable2 = *vm.getVariable(parameters.at(2));

	if (isUndefined(variable1, variable2, vm))
	{
		return;
	}

	if (variable1.getType() == VariableType::number && variable2.getType() == VariableType::number) 
	{
		int number1 = atoi(variable1.getValue().c_str());
		int number2 = atoi(variable2.getValue().c_str());

		vm.setReturnValue(to_string(number1 % number2));
	}
	else 
	{
		throwTypeError(variable1, variable2, vm);

		return;
	}
}

pair<string, string> ModuloCommand::accept(CommandVisitor& commandVisitor) 
{
	return commandVisitor.visit(*this);
}