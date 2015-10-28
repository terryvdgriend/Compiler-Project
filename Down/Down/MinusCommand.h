#pragma once
#include "BaseCommand.h"

class MinusCommand : public BaseCommand
{
	public:
		void execute(VirtualMachine& vm, vector<string>& parameters);
};