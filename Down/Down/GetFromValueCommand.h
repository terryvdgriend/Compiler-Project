#pragma once
#include "BaseCommand.h"

class GetFromValueCommand : public BaseCommand
{
	public:
		void execute(VirtualMachine& vm, AbstractFunctionCall& node);
		/*virtual*/ pair<string, string> accept(class CommandVisitor &cmdVisitor);
};