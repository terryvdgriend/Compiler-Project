#include "stdafx.h"
#include "DivideCommand.h"
#include "MandatoryCommandIncludes.h"

void DivideCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();

	shared_ptr<Variable> variable1 = vm.getVariable(parameters.at(1));
	shared_ptr<Variable> variable2 = vm.getVariable(parameters.at(2));

	if (isUndefined(*variable1, *variable2, vm))
	{
		return;
	}

	if (variable1->getType() == VariableType::number && variable2->getType() == VariableType::number)
	{
		int number1 = atoi(variable1->getValue().c_str());
		int number2 = atoi(variable2->getValue().c_str());

		if (number2 != 0) 
		{
			vm.setReturnValue(to_string(number1 / number2));
		}
		else 
		{
			ErrorHandler::getInstance()->addError(make_shared<Error>("Divide by 0", ".md", -1, -1, ErrorType::ERROR));
			vm.triggerRunFailure();

			return;
		}
	}
	else 
	{
		// Exception division requires 2 numbers
		throwTypeError(*variable1, *variable2, vm);

		return;
	}
}

pair<string, string> DivideCommand::accept(CommandVisitor& commandVisitor)
{
	return commandVisitor.visit(*this);
}