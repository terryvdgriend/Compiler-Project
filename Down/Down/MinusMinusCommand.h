#pragma once
#include "BaseCommand.h"

class MinusMinusCommand : public BaseCommand
{
	public:
		MinusMinusCommand();
		~MinusMinusCommand();
		void execute(VirtualMachine *vm, vector<string> *parameters);
};