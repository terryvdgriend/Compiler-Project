#pragma once
#include "BaseCommand.h"

class EqualsToCommand : public BaseCommand
{
	public:
		void execute(VirtualMachine& vm, vector<string>& parameters);
};