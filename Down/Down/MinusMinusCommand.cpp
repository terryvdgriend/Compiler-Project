#include "stdafx.h"
#include "MinusMinusCommand.h"
#include "CommandVisitor.h"

void MinusMinusCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();

	Variable variable = *vm.getVariable(parameters[1]);

	if (variable.getType() == VariableType::NULLTYPE)
	{
		variable = *vm.getVariable(parameters[2]);
		parameters[1] = parameters[2];
	}

	if (variable.getType() != VariableType::NULLTYPE && variable.getTokenType() == Token::TYPE_NUMBER)
	{
		double number1 = atof(variable.getValue().c_str()) - 1;

		for (std::string & item : vm.getFunctionParametersByKey(parameters.at(1))) {
			vm.setVariable(item, to_string(number1), variable.getTokenType());
		}
	}
}

std::pair<string, string> MinusMinusCommand::accept(CommandVisitor& commandVisitor) {
	return commandVisitor.visit(*this);
}