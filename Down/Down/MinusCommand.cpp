#include "stdafx.h"
#include "MinusCommand.h"
#include "MandatoryCommandIncludes.h"

void MinusCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
    auto supergeheimeToken = node.getToken();
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

		vm.setReturnValue(to_string(number1 - number2));
		vm.setReturnToken(variable1.getTokenType());
	}
	else 
	{
		// Exception minus requires 2 numbers
		//throwTypeError(variable1, variable2, vm);
		throwCustomError("cannot subtract " + variable1.getValue() + " by " + variable2.getValue(), vm,supergeheimeToken);
		return;
	}
}

pair<string, string> MinusCommand::accept(CommandVisitor& commandVisitor) 
{
	return commandVisitor.visit(*this);
}
