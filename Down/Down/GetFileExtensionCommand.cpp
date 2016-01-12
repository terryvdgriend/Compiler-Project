#include "stdafx.h"
#include "GetFileExtensionCommand.h"
#include "MandatoryCommandIncludes.h"

void GetFileExtensionCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();
	shared_ptr<Variable> variable = vm.getVariable(parameters.at(1));

	if (variable->getTokenType() == IToken::TYPE_TEXT) 
	{
		string fileName = variable->getValue();
		string::size_type idx;
		string fileExtension = "";
		idx = fileName.rfind('.');

		if (idx != string::npos)
		{
			fileExtension = "\"" + fileName.substr(idx + 1) + "\"";
		}
		vm.setReturnValue(fileExtension);
		vm.setReturnToken(variable->getTokenType());
	}
}

pair<string, string> GetFileExtensionCommand::accept(CommandVisitor& cmdVisitor)
{
	return cmdVisitor.visit(*this);
}