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

	if (variable1.getTokenType() == IToken::TYPE_NUMBER && variable2.getTokenType() == IToken::TYPE_NUMBER) {

		double number1 = atof(variable1.getValue().c_str());
		double number2 = atof(variable2.getValue().c_str());

		vm.setReturnValue(to_string(number1 + number2));
		vm.setReturnToken(variable1.getTokenType());
	}
	else if (variable1.getTokenType() == IToken::TYPE_FACT && variable2.getTokenType() == IToken::TYPE_FACT) {
		bool bool1 = (variable1.getValue() == "true") ? true : false;
		bool bool2 = (variable2.getValue() == "true") ? true : false;

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
	else {
		string var1 = variable1.getValue();
		string var2 = variable2.getValue();

		if (variable1.getTokenType() == IToken::TYPE_NUMBER) {
			var1 = removeUnnecessaryDotsAndZeros(var1);
		}
		if (variable1.getTokenType() == IToken::TYPE_NUMBER) {
			var2 = removeUnnecessaryDotsAndZeros(var2);
		}
		vm.setReturnValue(var1 + var2);
		vm.setReturnToken(IToken::TYPE_TEXT);
	}
}

pair<string, string> PlusCommand::accept(CommandVisitor& commandVisitor) 
{
	return commandVisitor.visit(*this);
}