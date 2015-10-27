#pragma once
#include "BaseCommand.h"

class ReturnToVariableCommand : public BaseCommand
{
	public:
		ReturnToVariableCommand();
		~ReturnToVariableCommand();
		void execute(VirtualMachine *vm, vector<string> *parameters);
};