#pragma once
#include "BaseCommand.h"

class EqualsToCommand : public BaseCommand
{
	public:
		void execute(VirtualMachine& vm, vector<string>& parameters);
		/*virtual*/ pair<string, string> accept(class CommandVisitor &cmdVisitor);
};