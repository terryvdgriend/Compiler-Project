#include "stdafx.h"
#include "CountCommand.h"
#include "MandatoryCommandIncludes.h"

void CountCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();
	shared_ptr<Variable> var = vm.getVariable(parameters[1]);

	if (var->getTokenType() != IToken::TYPE_FACT_ARRAY && var->getTokenType() != IToken::TYPE_NUMBER_ARRAY && var->getTokenType() != IToken::TYPE_TEXT_ARRAY) 
	{
		throwTypeError(*var, *var, vm);

		return;
	}
	shared_ptr<Array> array =  vm.getVariableArray(parameters[1]);
	vm.setReturnValue(to_string(array->variableArrayDictionary.size()));
	vm.setReturnToken(IToken::TYPE_NUMBER);
}

pair<string, string> CountCommand::accept(CommandVisitor& cmdVisitor)
{
	return cmdVisitor.visit(*this);
}