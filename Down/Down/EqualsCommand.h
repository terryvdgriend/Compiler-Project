#pragma once
#include "BaseCommand.h"

class EqualsCommand : public BaseCommand
{
	public:
		~EqualsCommand();
		void execute(VirtualMachine *vm, vector<string> *parameters);
};