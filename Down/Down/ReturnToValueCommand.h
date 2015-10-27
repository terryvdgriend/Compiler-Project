#pragma once
#include "BaseCommand.h"

class ReturnToValueCommand : public BaseCommand
{
	public:
		ReturnToValueCommand();
		~ReturnToValueCommand();
		void execute(VirtualMachine *vm, vector<string> *parameters);
};