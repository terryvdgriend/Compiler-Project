#pragma once
#include "BaseCommand.h"

class GreaterEqualsToCommand : public BaseCommand
{
	public:
		void execute(VirtualMachine& vm, vector<string>& parameters);
};