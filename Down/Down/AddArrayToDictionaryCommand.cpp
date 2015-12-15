#include "stdafx.h"
#include "AddArrayToDictionaryCommand.h"
#include "MandatoryCommandIncludes.h"

void AddArrayToDictionaryCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();

	for (string& item : vm.getFunctionParametersByKey(parameters[1])) 
	{
		vector<shared_ptr<Variable>> tempArray = vm.getVariableArray(item);

		if (item != parameters[1] && (size_t)atoi(vm.getReturnValue().c_str()) < tempArray.size())
		{
			vm.setReturnValue(to_string(tempArray.size()));
		}
	}

	if (vm.getReturnValue() != "")
	{
		vm.addArrayToDictionary(parameters.at(1), atoi(vm.getReturnValue().c_str()));
	}
	else
	{
		for (string& sItem : vm.getFunctionParametersByKey(parameters.at(1)))
		{
			vector<shared_ptr<Variable>> itemList = vm.getVariableArray(sItem);

			if (itemList.size() > 0)
			{
				vm.addArrayToDictionary(parameters.at(1), itemList.size());

				for (shared_ptr<Variable> var : itemList)
				{
					vm.addItemToVariableArray(parameters.at(1), var);
				}
			}
			else
			{
				ErrorHandler::getInstance()->addError(make_shared<Error>("the array is empty", ".md", -1, -1, ErrorType::ERROR));
			}
		}
	}
}

pair<string, string> AddArrayToDictionaryCommand::accept(CommandVisitor& commandVisitor)
{
	return commandVisitor.visit(*this);
}