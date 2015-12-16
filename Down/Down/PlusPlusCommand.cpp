#include "stdafx.h"
#include "PlusPlusCommand.h"
#include "MandatoryCommandIncludes.h"

void PlusPlusCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();

	Variable variable = *vm.getVariable(parameters[1]);

	if (variable.getType() == VariableType::nulltype)
	{
		variable = *vm.getVariable(parameters[2]);
		parameters[1] = parameters[2];
	}

	if (variable.getType() != VariableType::nulltype && variable.getTokenType() == IToken::TYPE_NUMBER)
	{
		double number1 = atof(variable.getValue().c_str()) + 1;
		
		for (std::string & item : vm.getFunctionParametersByKey(parameters.at(1))) {
			vm.setVariable(item, to_string(number1), variable.getTokenType());
		}
	}
}

pair<string, string> PlusPlusCommand::accept(CommandVisitor& commandVisitor) 
{
	return commandVisitor.visit(*this);
}