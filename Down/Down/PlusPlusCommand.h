#pragma once
#include "BaseCommand.h"

class PlusPlusCommand : public BaseCommand
{
	public:
		PlusPlusCommand();
		~PlusPlusCommand();
		void execute(VirtualMachine *vm, vector<string> *parameters);
};