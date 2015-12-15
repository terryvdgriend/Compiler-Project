#include "stdafx.h"
#include "ShowUpFunctionCommand.h"
#include "MandatoryCommandIncludes.h"

void ShowUpFunctionCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();

	Variable variable2 = *vm.getVariable(parameters.at(1));
	string val = "";

	if (variable2.getType() != VariableType::nulltype)
	{
		val += variable2.getValue();
	}
	val.erase(remove(val.begin(), val.end(), '\"'), val.end());
	cout << "UP: " + val << endl;
}

pair<string, string> ShowUpFunctionCommand::accept(CommandVisitor& cmdVisitor)
{
	return pair<string, string>();
}