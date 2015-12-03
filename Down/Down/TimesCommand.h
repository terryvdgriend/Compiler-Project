#pragma once
#include "BaseCommand.h"

class TimesCommand : public BaseCommand
{
	public:
		void execute(VirtualMachine& vm, AbstractFunctionCall& node);
		/*virtual*/ pair<string, string> accept(CommandVisitor &cmdVisitor);
};