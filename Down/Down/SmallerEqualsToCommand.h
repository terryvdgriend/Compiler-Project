#pragma once
#include "BaseCommand.h"

class SmallerEqualsToCommand : public BaseCommand
{
	public:
		SmallerEqualsToCommand();
		~SmallerEqualsToCommand();
		void execute(VirtualMachine *vm, vector<string> *parameters);
};