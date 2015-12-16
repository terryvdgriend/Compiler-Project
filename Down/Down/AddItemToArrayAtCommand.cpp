#include "stdafx.h"
#include "AddItemToArrayAtCommand.h"
#include "MandatoryCommandIncludes.h"

void AddItemToArrayAtCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();

	string param1 = vm.getFunctionParameterValueByKey(parameters[1]);
	shared_ptr<Variable> param2 = vm.getVariable(parameters[2]);
	shared_ptr<Variable> param3 = vm.getVariable(parameters[3]);

	list<string> functionParams = vm.getFunctionParametersByKey(parameters[1]);

	string key = param2->getValue();
	string value = param3->getValue();
	string arrayKey = functionParams.back();

	if (key != "" && value != "" && arrayKey != "" && param2->getType() == VariableType::number)
	{
		VariableType arrayType = param3->getType();
		pair<string, string> arrayTypes = vm.getVariableTypeSameAsArrayType(param1, param3->getTokenType());

		if (arrayTypes.first != arrayTypes.second)
		{
            auto var1  = Variable(arrayTypes.second);
            auto var2   = Variable(arrayTypes.first);
			throwTypeError(var1,var2 , vm);
		}
		else
		{
			for (string& temp : functionParams)
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

					if (isAnArrayWithItems) 
					{ 
						arrayWithItems = vm.getVariableArray(temp); 
					}

					if (arrayWithItems.size() > (size_t)0 && (size_t)atoi(key.c_str()) >= arrayWithItems.size())
					{
                        auto error = make_shared<Error>("index out of bounds", ".md", -1, -1, ErrorType::ERROR);
						ErrorHandler::getInstance()->addError(error);
						vm.triggerRunFailure();

						return;
					}

					for (int i = 0; (size_t)i < arrayWithItems.size(); i++)
					{
						if (arrayWithItems[i])
						{
							vm.addItemToVariableArrayAt(arrayKey, to_string(i), arrayWithItems[i]);
						}
					}

					break;
				}
			}

			for (string& item : functionParams)
			{
				vm.addItemToVariableArrayAt(item, key, param3);
			}
		}
	}
	else
	{
		if (key == "") 
		{
            auto error = make_shared<Error>("you want to add an item to an array, but the key is empty", ".md", -1, -1, ErrorType::ERROR);
			ErrorHandler::getInstance()->addError(error);
			vm.triggerRunFailure(); 
		}
		else if (value == "") 
		{
            auto error = make_shared<Error>("you want to add an item to an array, but the value is empty", ".md", -1, -1, ErrorType::ERROR);
			ErrorHandler::getInstance()->addError(error);
			vm.triggerRunFailure(); 
		}
		else if (arrayKey == "") 
		{
            auto error = make_shared<Error>("you want to add an item to an array, but the array is undefined", ".md", -1, -1, ErrorType::ERROR);
			ErrorHandler::getInstance()->addError(error);
			vm.triggerRunFailure();
		}
		else if (param2->getType() != VariableType::number) 
		{
            auto error = make_shared<Error>("you want to set an item from an array, but the index isn't a number", ".md", -1, -1, ErrorType::ERROR);
			ErrorHandler::getInstance()->addError(error);
			vm.triggerRunFailure(); 
		}
	}
	}

pair<string, string> AddItemToArrayAtCommand::accept(CommandVisitor& commandVisitor) 
{
	return commandVisitor.visit(*this);
}
