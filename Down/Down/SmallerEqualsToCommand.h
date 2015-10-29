#pragma once
#include "BaseCommand.h"

class SmallerEqualsToCommand : public BaseCommand
{
	public:
		void execute(VirtualMachine& vm, vector<string>& parameters);
};