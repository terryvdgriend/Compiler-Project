#include "stdafx.h"
#include "AddLengthToArrayCommand.h"
#include "MandatoryCommandIncludes.h"

void AddLengthToArrayCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();
	if (parameters.size() > 3) {
		string retVal = "";
		for (size_t i = 1; i < parameters.size()-1; i++)
		{
			if (i != parameters.size() - 2) {
				retVal += vm.getVariable(parameters.at(i))->getValue() + ";";
			}
			else
				retVal += vm.getVariable(parameters.at(i))->getValue();
		}
		vm.setReturnValue(retVal);
	}
	else
		vm.setReturnValue(vm.getVariable(parameters[1])->getValue());
}

pair<string, string> AddLengthToArrayCommand::accept(CommandVisitor& commandVisitor) 
{
	return commandVisitor.visit(*this);
}