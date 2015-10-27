#pragma once
#include "BaseCommand.h"

class MinusCommand : public BaseCommand
{
	public:
		~MinusCommand();
		void execute(VirtualMachine *vm, vector<string> *parameters);
};