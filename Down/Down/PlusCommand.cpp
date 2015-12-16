#include "stdafx.h"
#include "PlusCommand.h"
#include "MandatoryCommandIncludes.h"

void PlusCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
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

		vm.setReturnValue(to_string(number1 + number2));
		vm.setReturnToken(variable1.getTokenType());
	}
	else if (variable1.getType() == VariableType::fact && variable2.getType() == VariableType::fact) 
	{
		bool bool1 = false;
		bool bool2 = false;

		if (variable1.getValue() == "true")
		{
			bool1 = true;
		}

		if (variable2.getValue() == "true")
		{
			bool2 = true;
		}
		bool outcome = bool1 + bool2;

		if (outcome)
		{
			vm.setReturnValue("true");
		}
		else
		{
			vm.setReturnValue("false");
		}
		vm.setReturnToken(variable1.getTokenType());
	}
	else 
	{
		vm.setReturnValue(variable1.getValue() + variable2.getValue());
		vm.setReturnToken(IToken::TYPE_TEXT);
	}
}

pair<string, string> PlusCommand::accept(CommandVisitor& commandVisitor) 
{
	return commandVisitor.visit(*this);
}