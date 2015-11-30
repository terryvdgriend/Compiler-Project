#include "stdafx.h"
#include "DivideCommand.h"
#include "CommandVisitor.h"

void DivideCommand::execute(VirtualMachine& vm, vector<string>& parameters)
{
	Variable variable1 = *vm.getVariable(parameters.at(1));
	Variable variable2 = *vm.getVariable(parameters.at(2));

	if (isUndefined(variable1, variable2, vm))
		return;

	if (variable1.getType() == VariableType::NUMBER && variable2.getType() == VariableType::NUMBER) {

		int number1 = atoi(variable1.getValue().c_str());
		int number2 = atoi(variable2.getValue().c_str());

		if (number2 != 0) {
			vm.setReturnValue(to_string(number1 / number2));
		}
		else {
			// Exception delen door 0
			ErrorHandler::getInstance()->addError(Error{ "Divide by 0", ".md", -1, -1, Error::error });
			vm.triggerRunFailure();
			return;
		}
	}
	else {
		// Exception delen heeft 2 nummers nodig
		throwTypeError(variable1, variable2, vm);
		return;
	}
}

std::pair<string, string> DivideCommand::accept(CommandVisitor& commandVisitor) {
	return commandVisitor.visit(*this);
}