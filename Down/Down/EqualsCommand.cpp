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
	auto toArray = vm.getVariableArray(parameters[1]);
	auto fromArray = vm.getVariableArray(parameters[2]);

	string buffer;
	
	string localVariable;

	if (toArray.size() == 0) {
		vm.addArrayToDictionary(parameters[1], fromArray.size());
		for (size_t i = 0; i < fromArray.size(); i++)
		{
			CompileSingleStatement varGetter = CompileSingleStatement();
			localVariable = varGetter.getNextLocalVariableName(buffer);
			vm.setVariable(localVariable, fromArray.at(i)->getValue(), fromArray.at(i)->getTokenType());
			vm.addItemToVariableArrayAt(parameters[1], to_string(i), vm.getVariable(localVariable));
		}
		// create Array
		//set old array to this array
	}
	else if(toArray.size() >= fromArray.size()) {
		//set old array to this array
	}
	else {
		// throw error index out of bounds
	}

}