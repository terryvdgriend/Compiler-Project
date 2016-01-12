#include "stdafx.h"
#include "CountCommand.h"
#include "MandatoryCommandIncludes.h"

CountCommand::CountCommand()
{
}


CountCommand::~CountCommand()
{
}

void CountCommand::execute(VirtualMachine & vm, AbstractFunctionCall & node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();
	auto var = vm.getVariable(parameters[1]);
	if (var->getTokenType() != IToken::TYPE_FACT_ARRAY && var->getTokenType() != IToken::TYPE_NUMBER_ARRAY && var->getTokenType() != IToken::TYPE_TEXT_ARRAY) {
		throwTypeError(*var, *var, vm);
		return;
	}
	auto array =  vm.getVariableArray(parameters[1]);
	if (array != nullptr) {
		if (parameters.size() > 2) {
			auto var = vm.getVariable(parameters[2]);
			if (var->getTokenType() == IToken::TYPE_NUMBER && var->getType() == VariableType::number) {
				int index = atof(var->getValue().c_str());
				if (index < 0) {
					throwCustomError("index is below zero.", vm);
				}
				else if (index > array->arraySizes.size() - 1) {
					throwCustomError("index out of bounds range.", vm);
				}
				else {
					vm.setReturnValue(to_string(array->arraySizes.at(index)));
					vm.setReturnToken(IToken::TYPE_NUMBER);
				}
			}
			else {
				throwCustomError("input is not a number.", vm);
			}
		}
		else {
			vm.setReturnValue(to_string(array->variableArrayDictionary.size()));
			vm.setReturnToken(IToken::TYPE_NUMBER);
		}
	}
	else {
		throwCustomError("array is not found.", vm);
	}
	

}

pair<string, string> CountCommand::accept(CommandVisitor & cmdVisitor)
{
	return cmdVisitor.visit(*this);
}
