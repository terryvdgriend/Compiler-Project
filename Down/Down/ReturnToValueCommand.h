#pragma once
#include "BaseCommand.h"

class ReturnToValueCommand : public BaseCommand
{
	public:
		void execute(VirtualMachine& vm, vector<string>& parameters);
};