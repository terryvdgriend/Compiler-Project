#include "stdafx.h"
#include "AddItemToArrayAtCommand.h"
#include "CommandVisitor.h"

pair<string, string> AddItemToArrayAtCommand::accept(CommandVisitor& commandVisitor) {
	return commandVisitor.visit(*this);
}

void AddItemToArrayAtCommand::execute(VirtualMachine & vm, AbstractFunctionCall & node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();

	string param1 = vm.getFunctionParameterValueByKey(parameters[1]);
	shared_ptr<Variable> param2 = vm.getVariable(parameters[2]);
	shared_ptr<Variable> param3 = vm.getVariable(parameters[3]);

	list<string> functionParams = vm.getFunctionParametersByKey(parameters[1]);

	string key = param2->getValue();
	string value = param3->getValue();
	string arrayKey = functionParams.back();

	if (key != "" && value != "" && arrayKey != "" && param2->getType() == VariableType::NUMBER)
	{
		VariableType arrayType = param3->getType();
		if (!vm.isVariableTypeSameAsArrayType(param1, param3->getTokenType()))
		{
			throwTypeError(*param2, *param3, vm);
			//ErrorHandler::getInstance()->addError(Error{ "you want to add an item to an array, but the type isn't aloud in this array", ".md", -1, -1, Error::error });
		}
		else
		{
			for (string & temp : functionParams)
			{
				if (temp == parameters[1])
				{
					bool isAnArrayWithItems = false;
					vector<shared_ptr<Variable>> arrayWithItems;
					for (shared_ptr<Variable> v : vm.getVariableArray(temp))
					{
						if (v)
						{
							isAnArrayWithItems = true;
							break;
						}
					}
					if (isAnArrayWithItems) { arrayWithItems = vm.getVariableArray(temp); }
					if (arrayWithItems.size() > 0 && atoi(key.c_str()) >= arrayWithItems.size()) {
						ErrorHandler::getInstance()->addError(Error{ "index out of bounds", ".md", -1, -1, Error::error });
						vm.triggerRunFailure();
						return;
					}
					for (int i = 0; i < arrayWithItems.size(); i++)
					{
						if (arrayWithItems[i])
						{
							vm.addItemToVariableArrayAt(arrayKey, to_string(i), arrayWithItems[i]);
						}
					}

					
					break;
				}
			}
			for (string & item : functionParams) {
				vm.addItemToVariableArrayAt(item, key, param3);
			}
		}
	}
	else
	{
		if (key == "") { ErrorHandler::getInstance()->addError(Error{ "you want to add an item to an array, but the key is empty", ".md", -1, -1, Error::error }); vm.triggerRunFailure(); }
		else if (value == "") { ErrorHandler::getInstance()->addError(Error{ "you want to add an item to an array, but the value is empty", ".md", -1, -1, Error::error });vm.triggerRunFailure(); }
		else if (arrayKey == "") { ErrorHandler::getInstance()->addError(Error{ "you want to add an item to an array, but the array is undefined", ".md", -1, -1, Error::error }); vm.triggerRunFailure();}
		else if (param2->getType() != VariableType::NUMBER) { ErrorHandler::getInstance()->addError(Error{ "you want to set an item from an array, but the index isn't a number", ".md", -1, -1, Error::error });vm.triggerRunFailure(); }
	}
}
