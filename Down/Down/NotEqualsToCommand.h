#pragma once
#include "BaseCommand.h"

class NotEqualsToCommand : public BaseCommand
{
	public:
		void execute(VirtualMachine& vm, vector<string>& parameters);
};