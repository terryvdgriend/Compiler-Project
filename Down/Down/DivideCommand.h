#pragma once
#include "BaseCommand.h"

class DivideCommand : public BaseCommand
{
	public:
		void execute(VirtualMachine& vm, vector<string>& parameters);
};