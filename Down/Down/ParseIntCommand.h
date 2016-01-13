#pragma once
#include "BaseCommand.h"

class ParseIntCommand :	public BaseCommand
{
	public:
		void execute(VirtualMachine& vm, AbstractFunctionCall& node);
		pair<string, string> accept(CommandVisitor& cmdVisitor);

	private:
		bool is_number(const string& s);
};