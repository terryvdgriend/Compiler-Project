#pragma once
#include "BaseCommand.h"

class SmallerThanCommand : public BaseCommand
{
	public:
		void execute(VirtualMachine& vm, AbstractFunctionCall& node);
		/*virtual*/ pair<string, string> accept(class CommandVisitor &cmdVisitor);
};