#include "stdafx.h"
#include "DivideCommand.h"
#include "MandatoryCommandIncludes.h"

void DivideCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
    auto supergeheimeToken = node.getToken();
	vector<string>& parameters = node.getContentArrayNonConstant();

	shared_ptr<Variable> variable1 = vm.getVariable(parameters.at(1));
	shared_ptr<Variable> variable2 = vm.getVariable(parameters.at(2));

	if (isUndefined(*variable1, *variable2, vm))
	{
		return;
	}

	if (variable1->getTokenType() == IToken::TYPE_NUMBER && variable2->getTokenType() == IToken::TYPE_NUMBER) 
	{
		double number1 = atof(variable1->getValue().c_str());
		double number2 = atof(variable2->getValue().c_str());

		if (number2 != 0) 
		{
			vm.setReturnValue(to_string(number1 / number2));
			vm.setReturnToken(variable1->getTokenType());
		}
		else 
		{
			throwCustomError("cannot divide by zero", vm,supergeheimeToken);
			return;
		}
	}
	else 
	{
		Variable variable1 = *vm.getVariable(parameters.at(1));
		Variable variable2 = *vm.getVariable(parameters.at(2));
		// Exception division requires 2 numbers
		throwCustomError("cannot divide " + variable1.getValue() + " by " + variable2.getValue(), vm, supergeheimeToken);

		return;
	}
}

pair<string, string> DivideCommand::accept(CommandVisitor& commandVisitor)
{
	return commandVisitor.visit(*this);
}