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
	vm.setReturnValue(to_string(array.size()));
	vm.setReturnToken(IToken::TYPE_NUMBER);
}

pair<string, string> CountCommand::accept(CommandVisitor & cmdVisitor)
{
	return cmdVisitor.visit(*this);
}
