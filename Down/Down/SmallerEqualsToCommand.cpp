#include "stdafx.h"
#include "SmallerEqualsToCommand.h"

void SmallerEqualsToCommand::execute(VirtualMachine& vm, vector<string>& parameters)
{
	Variable variable1 = *vm.getVariable(parameters.at(1));
	Variable variable2 = *vm.getVariable(parameters.at(2));
	if (variable1.getType() == VariableType::NULLTYPE || variable1.getType() == VariableType::BOOL) {
		ErrorHandler::getInstance()->addError(Error{ "cannot compare " + variable1.getValue() + " and " + variable2.getValue(),".md", -1, -1, Error::error });
		vm.triggerRunFailure();
		return;
	}
	if (variable2.getType() == VariableType::NULLTYPE || variable2.getType() == VariableType::BOOL) {
		ErrorHandler::getInstance()->addError(Error{ "cannot compare " + variable2.getValue() + " and " + variable1.getValue(),".md", -1, -1, Error::error });
		vm.triggerRunFailure();
		return;
	}
	if (variable1.getType() == VariableType::NUMBER && variable2.getType() == VariableType::NUMBER) {
		int number1 = atoi(variable1.getValue().c_str());
		int number2 = atoi(variable2.getValue().c_str());
		if (number1 <= number2)
		{
			vm.setReturnValue("true");
		}
		else
		{
			vm.setReturnValue("false");
		}
	}
	else {
		// Exception "cannot compare different types than numbers"
	}
}