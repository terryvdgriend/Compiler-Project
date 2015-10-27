#pragma once
#include "BaseCommand.h"

class SmallerThanCommand : public BaseCommand
{
	public:
		SmallerThanCommand();
		~SmallerThanCommand();
		void execute(VirtualMachine *vm, vector<string> *parameters);
};