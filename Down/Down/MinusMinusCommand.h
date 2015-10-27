#pragma once
#include "BaseCommand.h"

class MinusMinusCommand : public BaseCommand
{
	public:
		~MinusMinusCommand();
		void execute(VirtualMachine *vm, vector<string> *parameters);
};