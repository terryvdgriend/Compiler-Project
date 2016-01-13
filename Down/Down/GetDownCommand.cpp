#include "stdafx.h"
#include "GetDownCommand.h"
#include "MandatoryCommandIncludes.h"

void GetDownCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	string input;
	cout << "> ";
	cin >> input;

	vm.setReturnValue(input);
	vm.setReturnToken(IToken::TYPE_TEXT);
}

pair<string, string> GetDownCommand::accept(CommandVisitor& cmdVisitor)
{
	return cmdVisitor.visit(*this);
}