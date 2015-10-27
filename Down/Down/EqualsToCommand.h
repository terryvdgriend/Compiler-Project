#pragma once
#include "BaseCommand.h"

class EqualsToCommand : public BaseCommand
{
	public:
		~EqualsToCommand();
		void execute(VirtualMachine *vm, vector<string> *parameters);
};