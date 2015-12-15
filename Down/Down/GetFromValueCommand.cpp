#include "stdafx.h"
#include "GetFromValueCommand.h"
#include <vector>
#include "CommandVisitor.h"

void GetFromValueCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();
	string rValue = vm.getReturnValue();
	Token::iToken rToken = vm.getReturnToken();
	if (&rValue != nullptr)
	{
		vm.setReturnValue("");
		vm.setReturnToken(Token::ANY);
		if (vm.isAnIdentifier(rValue))
		{
			if (!vm.hasValueInFunctionParameters(parameters[1]))
			{
				vector<string> value = vm.getFunctionParametersByValue(rValue);

				if (value.size() > 0)
				{
					vm.setVariable(parameters[1], vm.getVariable(value.back())->getValue(), rToken);
				}
				else
				{
					// Hier exception throwen var is undefined

					vm.setVariable(parameters[1], "", rToken);
				}
				vm.setFunctionParameter(parameters[1], rValue);
			}
		}
		else
		{
			vm.setVariable(parameters[1], rValue, rToken);
		}
	}
}

std::pair<string, string> GetFromValueCommand::accept(CommandVisitor& commandVisitor) {
	return commandVisitor.visit(*this);
}