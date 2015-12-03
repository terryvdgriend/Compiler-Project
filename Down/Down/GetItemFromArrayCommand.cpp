#include "stdafx.h"
#include "GetItemFromArrayCommand.h"
#include "CommandVisitor.h"

pair<string, string> GetItemFromArrayCommand::accept(CommandVisitor& commandVisitor) {
	return commandVisitor.visit(*this);
}

void GetItemFromArrayCommand::execute(VirtualMachine & vm, AbstractFunctionCall & node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();
	vector<shared_ptr<Variable>> varArray = vm.getVariableArray(parameters.at(1));

	if (varArray.size() <= 0)
	{
		string functParamByKey = vm.getFunctionParameterValueByKey(parameters.at(1));

		string tempKey;
		int tempSizePrev = 0, tempSizeCurr = 0;

		for (string functParamByValue : vm.getFunctionParametersByValue(functParamByKey))
		{
			for (shared_ptr<Variable> var : vm.getVariableArray(functParamByValue))
			{
				if (var->getType() != VariableType::NULLTYPE && var->getValue() != "")
				{
					tempSizeCurr++;
				}
			}
			if (tempSizePrev < tempSizeCurr)
			{
				tempSizePrev = tempSizeCurr;
				tempKey = functParamByValue;
			}
			tempSizeCurr = 0;
		}

		/*for (string functParamByValue : vm.getFunctionParametersByValue(functParamByKey))
		{*/
		vector<shared_ptr<Variable>> functParam = vm.getVariableArray(tempKey);
		int index = 0;

		if (functParam.size() > 0)
		{
			vm.addArrayToDictionary(parameters.at(1), functParam.size());

			for (shared_ptr<Variable> var : functParam)
			{
				//if (var.getValue() == "" && var.getType() < 0) continue;
				vm.addItemToVariableArrayAt(parameters.at(1), to_string(index), var);
				index++;
			}

			varArray = vm.getVariableArray(parameters.at(1));
			//break;
		}
		//}
	}

	if (varArray.size() > 0)
	{
		shared_ptr<Variable> variable1 = vm.getVariable(parameters.at(2));
		if (varArray.at(atoi(variable1->getValue().c_str()))) {
			vm.setReturnValue(varArray.at(atoi(variable1->getValue().c_str()))->getValue());
			vm.setReturnToken(varArray.at(atoi(variable1->getValue().c_str()))->getTokenType());
		}
		else {
			string index = variable1->getValue().c_str();
			ErrorHandler::getInstance()->addError(Error{ "array index "+ index +" is undefined", ".md", -1, -1, Error::error });
			vm.triggerRunFailure();
			return;
		}

	}
	else
	{
		ErrorHandler::getInstance()->addError(Error{ "the array is still empty", ".md", -1, -1, Error::error });
		vm.triggerRunFailure();
	}
}
