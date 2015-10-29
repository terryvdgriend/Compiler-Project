#pragma once
#include "BaseCommand.h"

class MinusMinusCommand : public BaseCommand
{
	public:
		void execute(VirtualMachine& vm, vector<string>& parameters);
};