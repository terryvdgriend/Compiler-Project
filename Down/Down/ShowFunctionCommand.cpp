#include "stdafx.h"
#include "ShowFunctionCommand.h"
#include "MandatoryCommandIncludes.h"

void ShowFunctionCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	string val = "";
	vector<string>& parameters = node.getContentArrayNonConstant();
	if (parameters.size() >= 2) {
		Variable variable2 = *vm.getVariable(parameters.at(1));

		if (variable2.getType() != VariableType::nulltype)
		{
			val += variable2.getValue();

			if (variable2.getTokenType() == IToken::TYPE_NUMBER)
			{
				val = removeUnnecessaryDotsAndZeros(val);
			}
		}
		val.erase(remove(val.begin(), val.end(), '\"'), val.end());
	}

	if (parameters.size() >= 3) 
	{
		Variable variable3 = *vm.getVariable(parameters.at(2));

		if (variable3.getType() != VariableType::nulltype)
		{
			val += " - "+variable3.getValue();

			if (variable3.getTokenType() == IToken::TYPE_NUMBER) 
			{
				val = removeUnnecessaryDotsAndZeros(val);
			}
		}
		val.erase(remove(val.begin(), val.end(), '\"'), val.end());
	}
	cout << val << endl;
}

pair<string, string> ShowFunctionCommand::accept(CommandVisitor& cmdVisitor)
{
	return pair<string, string>();
}