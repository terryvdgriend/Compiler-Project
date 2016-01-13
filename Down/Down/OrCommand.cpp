#include "stdafx.h"
#include "OrCommand.h"
#include "MandatoryCommandIncludes.h"


OrCommand::OrCommand()
{
}


OrCommand::~OrCommand()
{
}

void OrCommand::execute(VirtualMachine & vm, AbstractFunctionCall & node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();

	Variable variable1 = *vm.getVariable(parameters.at(1));
	Variable variable2 = *vm.getVariable(parameters.at(2));

	if (isUndefined(variable1, variable2, vm))
	{
		return;
	}

	if (variable1.getTokenType() == IToken::TYPE_FACT && variable1.getType() == VariableType::fact) {
		if (variable2.getTokenType() == IToken::TYPE_FACT && variable2.getType() == VariableType::fact) {
			vm.setReturnValue("false");
			vm.setReturnToken(IToken::TYPE_FACT);
			if (variable1.getValue() == "true") {
				vm.setReturnValue("true");
				return;
			}
			else if (variable2.getValue() == "true") {
				vm.setReturnValue("true");
				return;
			}
		}
		else {
			throwCustomError("second variable is not a bool",vm,node.getToken());
		}
	}
	else {
		throwCustomError("first variable is not a bool", vm, node.getToken());
	}
}

pair<string, string> OrCommand::accept(CommandVisitor & cmdVisitor)
{
	return cmdVisitor.visit(*this);
}
