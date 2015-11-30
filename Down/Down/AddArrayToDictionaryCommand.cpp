#include "stdafx.h"
#include "AddArrayToDictionaryCommand.h"
#include "CommandVisitor.h"

void AddArrayToDictionaryCommand::execute(VirtualMachine& vm, vector<string>& parameters)
{
	if (vm.getReturnValue() != "")
	{
		vm.addArrayToDictionary(parameters.at(1), atoi(vm.getReturnValue().c_str()));
	}
	else
	{
		for (string & sItem : vm.getFunctionParametersByKey(parameters.at(1)))
		{
			vector<Variable> itemList = vm.getVariableArray(sItem);
			if (itemList.size() > 0)
			{
				vm.addArrayToDictionary(parameters.at(1), itemList.size());
				for (Variable var : itemList)
				{
					vm.addItemToVariableArray(parameters.at(1), var);
				}
			}
			else
			{
				ErrorHandler::getInstance()->addError(Error{ "the array is empty", ".md", -1, -1, Error::error });
			}
		}
	}
}

pair<string, string> AddArrayToDictionaryCommand::accept(CommandVisitor& commandVisitor) {
	return commandVisitor.visit(*this);
}