#include "stdafx.h"
#include "ModuloCommand.h"
#include "MandatoryCommandIncludes.h"

void ModuloCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
    auto supergeheimeToken = node.getToken();
	vector<string>& parameters = node.getContentArrayNonConstant();

	Variable variable1 = *vm.getVariable(parameters.at(1));
	Variable variable2 = *vm.getVariable(parameters.at(2));

	if (isUndefined(variable1, variable2, vm))
	{
		return;
	}

	if (variable1.getTokenType() == IToken::TYPE_NUMBER && variable2.getTokenType() == IToken::TYPE_NUMBER)
	{
		int number1 = atoi(variable1.getValue().c_str());
		int number2 = atoi(variable2.getValue().c_str());

		vm.setReturnValue(to_string(number1 % number2));
		vm.setReturnToken(variable1.getTokenType());
	}
	else 
	{
		//throwTypeError(variable1, variable2, vm);
		throwCustomError("cannot get remainder (modulo) " + variable1.getValue() + " from " + variable2.getValue(), vm,supergeheimeToken);
		return;
	}
}

pair<string, string> ModuloCommand::accept(CommandVisitor& commandVisitor) 
{
	return commandVisitor.visit(*this);
}