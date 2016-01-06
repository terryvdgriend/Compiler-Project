#include "stdafx.h"
#include "EqualsCommand.h"
#include "MandatoryCommandIncludes.h"
#include "CompileSingleStatement.h"

void EqualsCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();

 	shared_ptr<Variable> variable1 = vm.getVariable(parameters.at(1));
	shared_ptr<Variable> variable2 = vm.getVariable(parameters.at(2));

	if (variable1->getTokenType() == variable2->getTokenType()) 
	{
		if (variable1->getTokenType() == IToken::TYPE_FACT_ARRAY || variable1->getTokenType() == IToken::TYPE_NUMBER_ARRAY || variable1->getTokenType() == IToken::TYPE_TEXT_ARRAY) {
			setArrayToArray(vm, parameters);
		}
		else {
			variable1 = variable2;

			for (string& item : vm.getFunctionParametersByKey(parameters.at(1)))
			{
				vm.setVariable(item, variable1->getValue(), variable1->getTokenType());
			}
		}
		
	}
	else 
	{
		throwTypeError(*variable1, *variable2, vm);
	}
}

pair<string, string> EqualsCommand::accept(CommandVisitor& commandVisitor) 
{
	return commandVisitor.visit(*this);
}

void EqualsCommand::setArrayToArray(VirtualMachine& vm, vector<string>& parameters) {
	//get both array's
	auto toIdentifier = parameters[1];
	auto toArray = vm.getVariableArray(toIdentifier);
	string functParamByKey = vm.getFunctionParameterValueByKey(toIdentifier);
	auto fromArray = vm.getVariableArray(parameters[2]);
	for (auto identifier : vm.getFunctionParametersByValue(functParamByKey)) {
		if(vm.isAnArrayIdentifier(identifier)){
			toArray = vm.getVariableArray(identifier);
			toIdentifier = identifier;
		}
	}
	if (toArray == nullptr) {
		auto arrayVar = vm.getVariable(toIdentifier);
		vm.setFunctionParameter(toIdentifier, functParamByKey);
		toArray = vm.addArrayToDictionary(toIdentifier, fromArray->arraySizes);
		vm.addIdentifer(functParamByKey);
	}
	
	if (toArray->variableArrayDictionary.size() == 0) {
		toArray = vm.addArrayToDictionary(toIdentifier, vector<int>({ fromArray->variableArrayDictionary.size() }));
		
	}
	if (toArray->variableArrayDictionary.size() >= fromArray->variableArrayDictionary.size()) {
		string buffer;
		string localVariable;
		CompileSingleStatement varGetter = CompileSingleStatement();
		for (size_t i = 0; i < fromArray->variableArrayDictionary.size(); i++)
		{
			
			localVariable = varGetter.getNextLocalVariableName(buffer);
			vm.setVariable(localVariable, fromArray->variableArrayDictionary.at(i)->getValue(), fromArray->variableArrayDictionary.at(i)->getTokenType());
			vm.addItemToVariableArrayAt(toIdentifier, vector<string>({ to_string(i) }), vm.getVariable(localVariable));
		}
	}
	else {
		throwCustomError("index out of bounds array", vm);
	}
}