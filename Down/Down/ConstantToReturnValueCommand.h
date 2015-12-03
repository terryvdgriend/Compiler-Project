#pragma once
#include "BaseCommand.h"

class ConstantToReturnValueCommand : public BaseCommand
{
	public:
		void execute(VirtualMachine& vm, AbstractFunctionCall& node);
		/*virtual*/ pair<string, string> accept(class CommandVisitor &cmdVisitor);
};