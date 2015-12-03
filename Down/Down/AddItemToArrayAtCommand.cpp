#include "stdafx.h"
#include "AddItemToArrayAtCommand.h"
#include "CommandVisitor.h"

pair<string, string> AddItemToArrayAtCommand::accept(CommandVisitor& commandVisitor) {
	return commandVisitor.visit(*this);
}

void AddItemToArrayAtCommand::execute(VirtualMachine & vm, AbstractFunctionCall & node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();
	// TODO: Errorhandling erbij maken (geen ander type kunnen gebruiken)

	Variable* param2 = vm.getVariable(parameters[2]).get();
	Variable* param3 = vm.getVariable(parameters[3]).get();

	vector<string> functionParams = vm.getFunctionParametersByKey(parameters[1]);

	string key = param2->getValue();
	string value = param3->getValue();
	string arrayKey = functionParams.back();

	if (key != "" && value != "" && arrayKey != "" && param2->getType() == VariableType::NUMBER)
	{
		// TODO: arrayType aanpassen naar het type van de array
		VariableType arrayType = param3->getType();
		if (param3->getType() != arrayType)
		{
			ErrorHandler::getInstance()->addError(Error{ "you want to add an item to an array, but the type isn't aloud in this array", ".md", -1, -1, Error::error });
		}
		else
		{
			for (string & temp : functionParams)
			{
				if (temp == parameters[1])
				{
					bool isAnArrayWithItems = false;
					vector<shared_ptr<Variable>> arrayWithItems;
					for (string s : functionParams)
					{
						for (shared_ptr<Variable> v : vm.getVariableArray(s))
						{
							if (v->getType() >= 0 && v->getValue() != "")
							{
								isAnArrayWithItems = true;
								break;
							}
						}
						if (isAnArrayWithItems) { arrayWithItems = vm.getVariableArray(s); }
					}
					for (int i = 0; i < arrayWithItems.size(); i++)
					{
						if (arrayWithItems[i]->getType() >= 0 && arrayWithItems[i]->getValue() != "")
						{
							vm.addItemToVariableArrayAt(arrayKey, to_string(i), arrayWithItems[i]);
						}
					}

					for (string & item : functionParams) {
						//vm.addItemToVariableArrayAt(item, key, value);
					}
					break;
				}
			}
		}
	}
	else
	{
		if (key == "") { ErrorHandler::getInstance()->addError(Error{ "you want to add an item to an array, but the key is empty", ".md", -1, -1, Error::error }); }
		else if (value == "") { ErrorHandler::getInstance()->addError(Error{ "you want to add an item to an array, but the value is empty", ".md", -1, -1, Error::error }); }
		else if (arrayKey == "") { ErrorHandler::getInstance()->addError(Error{ "you want to add an item to an array, but the array is undefined", ".md", -1, -1, Error::error }); }
		else if (param2->getType() != VariableType::NUMBER) { ErrorHandler::getInstance()->addError(Error{ "you want to set an item from an array, but the index isn't a number", ".md", -1, -1, Error::error }); }
	}
}
