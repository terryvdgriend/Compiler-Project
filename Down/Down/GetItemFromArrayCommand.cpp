#include "stdafx.h"
#include "GetItemFromArrayCommand.h"
#include "MandatoryCommandIncludes.h"

void GetItemFromArrayCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
    auto supergeheimeToken = node.getToken();
	vector<string>& parameters = node.getContentArrayNonConstant();
	shared_ptr<Array> varArray = vm.getVariableArray(parameters.at(1));
	if (varArray == nullptr) {
		throwCustomError("array is not found.", vm, supergeheimeToken);
		return;
	}

	if (varArray->variableArrayDictionary.size() <= 0)
	{
		string functParamByKey = vm.getFunctionParameterValueByKey(parameters.at(1));
		string tempKey;
		int tempSizePrev = 0, tempSizeCurr = 0;

		for (string functParamByValue : vm.getFunctionParametersByValue(functParamByKey))
		{
			for (shared_ptr<Variable> var : vm.getVariableArray(functParamByValue)->variableArrayDictionary)
			{
				if (var->getType() != VariableType::nulltype && var->getValue() != "")
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
		vector<shared_ptr<Variable>> functParam = vm.getVariableArray(tempKey)->variableArrayDictionary;
		int index = 0;

		if (functParam.size() > 0)
		{
			vm.addArrayToDictionary(parameters.at(1), vector<int>({ static_cast<int>(functParam.size()) }));

			for (shared_ptr<Variable> var : functParam)
			{
				vm.addItemToVariableArrayAt(parameters.at(1), vector<string>({ to_string(index) }), var);
				index++;
			}
			varArray = vm.getVariableArray(parameters.at(1));
		}
	}

	if (varArray->variableArrayDictionary.size() > 0)
	{
		vector<int> indexArray;

		for (size_t i = 2; i < parameters.size(); i++)
		{
			indexArray.push_back(atoi(vm.getVariable(parameters.at(i))->getValue().c_str()));
		}
		shared_ptr<Variable> variable = vm.getItemFromVariableArray(parameters.at(1),indexArray);

		if (variable) 
		{
			vm.setReturnValue(variable->getValue());
			vm.setReturnToken(variable->getTokenType());
		}
		else 
		{
			vm.setReturnValue("");
			vm.setReturnToken(IToken::NONE);
		}
	}
	else
	{
		shared_ptr<Error> error = make_shared<Error>("the array is still empty", ".md", supergeheimeToken->getLineNumber(), supergeheimeToken->getPosition(), ErrorType::ERROR);
		ErrorHandler::getInstance()->addError(error);
		vm.triggerRunFailure();
	}
}

pair<string, string> GetItemFromArrayCommand::accept(CommandVisitor& commandVisitor) 
{
	return commandVisitor.visit(*this);
}