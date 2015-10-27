#pragma once
#include "BaseCommand.h"

class GreaterThanCommand : public BaseCommand
{
	public:
		~GreaterThanCommand();
		void execute(VirtualMachine *vm, vector<string> *parameters);
};