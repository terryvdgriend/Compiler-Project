#include "stdafx.h"
#include "AddArrayToDictionaryCommand.h"
#include "MandatoryCommandIncludes.h"

void AddArrayToDictionaryCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();
	string delimeter = ";";
	vector<int> multiLength;
	for (string& item : vm.getFunctionParametersByKey(parameters[1])) 
	{
		shared_ptr<Array> tempArray = vm.getVariableArray(item);
		int length = 0;
		size_t pos = 0;
		string returnVal = vm.getReturnValue();
		int count = 0;
		while ((pos = returnVal.find(delimeter)) != std::string::npos) {
			if (count == 0) {
				length = atoi(returnVal.substr(0, pos).c_str());
				count++;
			}
			else
				length = length * atoi(returnVal.substr(0, pos).c_str());
			multiLength.push_back(atoi(returnVal.substr(0, pos).c_str()));
			returnVal.erase(0, pos + delimeter.length());
		}
		if (count == 0) {
			length = atoi(returnVal.substr(0, pos).c_str());
		}
		else
			length = length * atoi(returnVal.substr(0, pos).c_str());
		multiLength.push_back(atoi(returnVal.c_str()));
		vm.setReturnValue(to_string(length));
		if (item != parameters[1] && (size_t)atoi(vm.getReturnValue().c_str()) < tempArray->variableArrayDictionary.size())
		{
			vm.setReturnValue(to_string(tempArray->variableArrayDictionary.size()));
		}
	}

	if (vm.getReturnValue() != "")
	{
		vm.addArrayToDictionary(parameters.at(1), multiLength);
	}
	else
	{
		for (string& sItem : vm.getFunctionParametersByKey(parameters.at(1)))
		{
			shared_ptr<Array> itemList = vm.getVariableArray(sItem);

			if (itemList->variableArrayDictionary.size() > 0)
			{
				vm.addArrayToDictionary(parameters.at(1), itemList->arraySizes);

				for (shared_ptr<Variable> var : itemList->variableArrayDictionary)
				{
					vm.addItemToVariableArray(parameters.at(1), var);
				}
			}
			else
			{
                auto error = make_shared<Error>("the array is empty", ".md", -1, -1, ErrorType::ERROR);
				ErrorHandler::getInstance()->addError(error);
			}
		}
	}
}

pair<string, string> AddArrayToDictionaryCommand::accept(CommandVisitor& commandVisitor)
{
	return commandVisitor.visit(*this);
}