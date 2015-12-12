#include "stdafx.h"
#include "ErrorCommand.h"

void ErrorCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();

	Variable variable2 = *vm.getVariable(parameters.at(1));
	string val = "";

	if (variable2.getType() != VariableType::NULLTYPE) {
		val += variable2.getValue();
	}
	
	ErrorHandler::getInstance()->addThrownError(val);

	val.erase(remove(val.begin(), val.end(), '\"'), val.end());
	cout << val << endl;
}

pair<string, string> ErrorCommand::accept(CommandVisitor & cmdVisitor)
{
	return pair<string, string>();
}