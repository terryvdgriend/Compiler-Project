#include "stdafx.h"
#include "EqualsCommand.h"
#include "MandatoryCommandIncludes.h"
#include "CompileSingleStatement.h"

void EqualsCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
    auto supergeheimeToken = node.getToken();
	vector<string>& parameters = node.getContentArrayNonConstant();

 	shared_ptr<Variable> variable1 = vm.getVariable(parameters.at(1));
	shared_ptr<Variable> variable2 = vm.getVariable(parameters.at(2));

	if (variable1->getTokenType() == variable2->getTokenType()) 
	{
		if (variable1->getTokenType() == IToken::TYPE_FACT_ARRAY || variable1->getTokenType() == IToken::TYPE_NUMBER_ARRAY || variable1->getTokenType() == IToken::TYPE_TEXT_ARRAY) 
		{
			setArrayToArray(vm, node);
		}
		else 
		{
			variable1 = variable2;

			for (string& item : vm.getFunctionParametersByKey(parameters.at(1)))
			{
				vm.setVariable(item, variable1->getValue(),supergeheimeToken, variable1->getTokenType());
			}
		}
	}
	else 
	{
		throwCustomError("Cannot assign " + variable1->getValue() + " with " + variable2->getValue(), vm, supergeheimeToken);
	}
}

pair<string, string> EqualsCommand::accept(CommandVisitor& commandVisitor) 
{
	return commandVisitor.visit(*this);
}

void EqualsCommand::setArrayToArray(VirtualMachine& vm, AbstractFunctionCall& node)
{
    auto supergeheimeToken = node.getToken();
	vector<string>& parameters = node.getContentArrayNonConstant();
	//get both array's
	string toIdentifier = parameters[1];
	shared_ptr<Array> toArray = vm.getVariableArray(toIdentifier);
	string functParamByKey = vm.getFunctionParameterValueByKey(toIdentifier);
	shared_ptr<Array> fromArray = vm.getVariableArray(parameters[2]);

	if (fromArray == nullptr) 
	{
		throwCustomError("array from is not set.", vm, supergeheimeToken);

		return;
	}

	for (auto identifier : vm.getFunctionParametersByValue(functParamByKey)) 
	{
		if (vm.isAnArrayIdentifier(identifier))
		{
			toArray = vm.getVariableArray(identifier);
			toIdentifier = identifier;
		}
	}

	if (toArray == nullptr) 
	{
		shared_ptr<Variable> arrayVar = vm.getVariable(toIdentifier);
		vm.setFunctionParameter(toIdentifier, functParamByKey);
		toArray = vm.addArrayToDictionary(toIdentifier, fromArray->arraySizes);
		vm.addIdentifer(functParamByKey);
	}
	
	if (toArray->variableArrayDictionary.size() == 0) 
	{
		toArray = vm.addArrayToDictionary(toIdentifier, vector<int>({ static_cast<int>(fromArray->variableArrayDictionary.size()) }));
	}

	if (toArray->variableArrayDictionary.size() >= fromArray->variableArrayDictionary.size())
	{
		string buffer;
		string localVariable;
		CompileSingleStatement varGetter = CompileSingleStatement();

		for (size_t i = 0; i < fromArray->variableArrayDictionary.size(); i++)
		{
			if (fromArray->variableArrayDictionary.at(i) != nullptr)
			{
				localVariable = varGetter.getNextLocalVariableName(buffer);
				vm.setVariable(localVariable, fromArray->variableArrayDictionary.at(i)->getValue(), supergeheimeToken, fromArray->variableArrayDictionary.at(i)->getTokenType());

				if (fromArray->arraySizes.size() > 1) 
				{
					vm.addItemToVariableArrayAt(toIdentifier,  to_string(i), vm.getVariable(localVariable));
				}
				else 
				{
					vm.addItemToVariableArrayAt(toIdentifier, vector<string>({ to_string(i) }), vm.getVariable(localVariable));
				}
			}
		}
	}
	else 
	{
		throwCustomError("index out of bounds array", vm, supergeheimeToken);
	}
}