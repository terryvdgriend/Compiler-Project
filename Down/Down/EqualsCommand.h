#pragma once
#include "BaseCommand.h"

class EqualsCommand : public BaseCommand
{
	public:
		void execute(VirtualMachine& vm, AbstractFunctionCall& node);
		pair<string, string> accept(CommandVisitor& cmdVisitor);

	private:
		void setArrayToArray(VirtualMachine& vm, AbstractFunctionCall & node);
};