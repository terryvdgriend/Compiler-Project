#pragma once
#include "BaseCommand.h"

class AddLengthToArrayCommand : public BaseCommand
{
	public:
		virtual void execute(VirtualMachine& vm, AbstractFunctionCall& node);
		pair<string, string> accept(CommandVisitor& cmdVisitor);
};