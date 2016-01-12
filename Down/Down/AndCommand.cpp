#include "stdafx.h"
#include "AndCommand.h"
#include "MandatoryCommandIncludes.h"

AndCommand::AndCommand()
{
}


AndCommand::~AndCommand()
{
}

void AndCommand::execute(VirtualMachine & vm, AbstractFunctionCall & node)
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
			bool one = (variable1.getValue() == "false") ? false : true;
			bool two = (variable2.getValue() == "false") ? false : true;
			bool outcome = (one && two);
			vm.setReturnValue(outcome ? "true" : "false");
			vm.setReturnToken(IToken::TYPE_FACT);
		}
		else {
			throwCustomError("second variable is not a bool", vm);
		}
	}
	else {
		throwCustomError("first variable is not a bool", vm);
	}
}

pair<string, string> AndCommand::accept(CommandVisitor & cmdVisitor)
{
	return cmdVisitor.visit(*this);
}
