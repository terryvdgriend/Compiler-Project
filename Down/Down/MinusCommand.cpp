#include "stdafx.h"
#include "MinusCommand.h"
#include "CommandVisitor.h"

void MinusCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();

	Variable variable1 = *vm.getVariable(parameters.at(1));
	Variable variable2 = *vm.getVariable(parameters.at(2));

	if (isUndefined(variable1, variable2, vm))
		return;

	if (variable1.getTokenType() == Token::TYPE_NUMBER && variable2.getTokenType() == Token::TYPE_NUMBER) {

		int number1 = atoi(variable1.getValue().c_str());
		int number2 = atoi(variable2.getValue().c_str());

		vm.setReturnValue(to_string(number1 - number2));
		vm.setReturnToken(variable1.getTokenType());
	}
	else {
		// Exception minus heeft 2 nummers nodig
		throwTypeError(variable1, variable2, vm);
		return;
	}
}

std::pair<string, string> MinusCommand::accept(CommandVisitor& commandVisitor) {
	return commandVisitor.visit(*this);
}
