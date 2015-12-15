#include "stdafx.h"
#include "RandomFunctionCommand.h"
#include "MandatoryCommandIncludes.h"

void RandomFunctionCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();

	Variable variable2 = *vm.getVariable(parameters.at(1));
	string val = "";

	if (variable2.getType() != VariableType::nulltype)
	{
		val += variable2.getValue();
	}
	val.erase(remove(val.begin(), val.end(), '\"'), val.end());
	vm.setReturnValue("666");
}

pair<string, string> RandomFunctionCommand::accept(CommandVisitor& cmdVisitor)
{
	return pair<string, string>();
}