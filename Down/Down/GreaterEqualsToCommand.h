#pragma once
#include "BaseCommand.h"

class GreaterEqualsToCommand : public BaseCommand
{
	public:
		GreaterEqualsToCommand();
		~GreaterEqualsToCommand();
		void execute(VirtualMachine *vm, vector<string> *parameters);
};