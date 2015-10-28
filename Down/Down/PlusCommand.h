#pragma once
#include "BaseCommand.h"

class PlusCommand : public BaseCommand
{
	public:
		void execute(VirtualMachine& vm, vector<string>& parameters);
};