#include "stdafx.h"
#include "ShowFunctionCommand.h"
#include "MandatoryCommandIncludes.h"

void ShowFunctionCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();

	Variable variable2 = *vm.getVariable(parameters.at(1));
	string val = "";

	if (variable2.getType() != VariableType::nulltype) 
	{
		val += variable2.getValue();
	}
	val.erase(remove(val.begin(), val.end(), '\"'), val.end());
	cout << val << endl;
}

pair<string, string> ShowFunctionCommand::accept(CommandVisitor& cmdVisitor)
{
	return pair<string, string>();
}