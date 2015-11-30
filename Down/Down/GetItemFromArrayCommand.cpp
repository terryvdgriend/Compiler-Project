#include "stdafx.h"
#include "GetItemFromArrayCommand.h"
#include "CommandVisitor.h"

void GetItemFromArrayCommand::execute(VirtualMachine& vm, vector<string>& parameters)
{
	vector<Variable> varArray = vm.getVariableArray(parameters.at(1));

	if (varArray.size() <= 0)
	{
		string functParamByKey = vm.getFunctionParameterValueByKey(parameters.at(1));

		for (string functParamByValue : vm.getFunctionParametersByValue(functParamByKey))
		{
			vector<Variable> functParam = vm.getVariableArray(functParamByValue);

			if (functParam.size() > 0)
			{
				vm.addArrayToDictionary(parameters.at(1), functParam.size());

				for (Variable var : functParam)
				{
					if (var.getValue() == "" && var.getType() < 0) break;
					vm.addItemToVariableArray(parameters.at(1), var);
				}

				varArray = vm.getVariableArray(parameters.at(1));
				break;
			}
		}
	}

	if (varArray.size() > 0)
	{
		shared_ptr<Variable> variable1 = vm.getVariable(parameters.at(2));
		vm.setReturnValue(varArray.at(atoi(variable1->getValue().c_str())).getValue());
	}
	else
	{
		ErrorHandler::getInstance()->addError(Error{ "the array is still empty", ".md", -1, -1, Error::error });
	}
}

pair<string, string> GetItemFromArrayCommand::accept(CommandVisitor& commandVisitor) {
	return commandVisitor.visit(*this);
}