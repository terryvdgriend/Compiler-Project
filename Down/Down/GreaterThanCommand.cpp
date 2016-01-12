#include "stdafx.h"
#include "GreaterThanCommand.h"
#include "MandatoryCommandIncludes.h"

void GreaterThanCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();

	Variable variable1 = *vm.getVariable(parameters.at(1));
	Variable variable2 = *vm.getVariable(parameters.at(2));

	if (isUndefined(variable1, variable2, vm))
	{
		return;
	}

	if (variable1.getTokenType() == IToken::TYPE_NUMBER && variable2.getTokenType() == IToken::TYPE_NUMBER) 
	{
		double number1 = atof(variable1.getValue().c_str());
		double number2 = atof(variable2.getValue().c_str());

		if (number1 > number2)
		{
			vm.setReturnValue("true");
		}
		else
		{
			vm.setReturnValue("false");
		}
		vm.setReturnToken(IToken::TYPE_FACT);
	}
	else 
	{
		// Exception "cannot compare different types than numbers"
		throwTypeError(variable1, variable2, vm);

		return;
	}
}

pair<string, string> GreaterThanCommand::accept(CommandVisitor& commandVisitor) 
{
	return commandVisitor.visit(*this);
}