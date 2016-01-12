#include "stdafx.h"
#include "TimesCommand.h"
#include "MandatoryCommandIncludes.h"

void TimesCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
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

		vm.setReturnValue(to_string(number1 * number2));
		vm.setReturnToken(variable1.getTokenType());
	}
	else 
	{
		Variable variable1 = *vm.getVariable(parameters.at(1));
		Variable variable2 = *vm.getVariable(parameters.at(2));
		// Exception division requires 2 numbers
		throwCustomError("cannot multiply " + variable1.getValue() + " by " + variable2.getValue(), vm, node.getToken());
		return;
	}
}

pair<string, string> TimesCommand::accept(CommandVisitor& commandVisitor) 
{
	return commandVisitor.visit(*this);
}