#pragma once
#include "BaseCommand.h"

class PlusCommand : public BaseCommand
{
	public:
		PlusCommand();
		~PlusCommand();
		void execute(VirtualMachine *vm, vector<string> *parameters);
};