#pragma once
#include "BaseCommand.h"

class ConstantToReturnValueCommand : public BaseCommand
{
	public:
		void execute(VirtualMachine& vm, AbstractFunctionCall& node);
		pair<string, string> accept(CommandVisitor& cmdVisitor);
};