#include "stdafx.h"
#include "EqualsToCommand.h"
#include "MandatoryCommandIncludes.h"

void EqualsToCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
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

		if (number1 == number2)
		{
			vm.setReturnValue("true");
			vm.setReturnToken(IToken::TYPE_FACT);
		}
		else
		{
			vm.setReturnValue("false");
			vm.setReturnToken(IToken::TYPE_FACT);
		}
	}
	else 
	{
		auto val1 = variable1.getValue();
		auto val2 = variable2.getValue();
		val1.erase(remove(val1.begin(), val1.end(), '\"'), val1.end());
		val2.erase(remove(val2.begin(), val2.end(), '\"'), val2.end());

		if (val1 == val2)
		{
			vm.setReturnValue("true");
			vm.setReturnToken(IToken::TYPE_FACT);
		}
		else
		{
			vm.setReturnValue("false");
			vm.setReturnToken(IToken::TYPE_FACT);
		}
	}
}

pair<string, string> EqualsToCommand::accept(CommandVisitor& commandVisitor) 
{
	return commandVisitor.visit(*this);
}