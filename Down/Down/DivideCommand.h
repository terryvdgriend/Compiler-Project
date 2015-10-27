#pragma once
#include "BaseCommand.h"

class DivideCommand : public BaseCommand
{
	public:
		DivideCommand();
		~DivideCommand();
		void execute(VirtualMachine *vm, vector<string> *parameters);
};