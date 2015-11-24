#include "stdafx.h"
#include "GetFromValueCommand.h"
#include <vector>
#include "CommandVisitor.h"

void GetFromValueCommand::execute(VirtualMachine& vm, vector<string>& parameters)
{
	string rValue = vm.getReturnValue();

	if (&rValue != nullptr)
	{
		if (vm.isAnIdentifier(rValue))
		{
			vm.setReturnValue("");

			if (!vm.hasValueInFunctionParameters(parameters[1]))
			{
				vector<string> value = vm.getFunctionParametersByValue(rValue);

				if (value.size() > 0)
				{
					vm.setVariable(parameters[1], vm.getVariable(value.back())->getValue());
				}
				else
				{
					// Hier exception throwen var is undefined

					vm.setVariable(parameters[1], "");
				}
				vm.setFunctionParameter(parameters[1], rValue);
			}
		}
		else
		{
			vm.setVariable(parameters[1], rValue);
		}
	}
}

std::pair<string, string> GetFromValueCommand::accept(CommandVisitor& commandVisitor) {
	return commandVisitor.visit(*this);
}