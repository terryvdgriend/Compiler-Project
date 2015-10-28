#pragma once
#include "BaseCommand.h"

class GreaterThanCommand : public BaseCommand
{
	public:
		void execute(VirtualMachine& vm, vector<string>& parameters);
};