#pragma once
#include "BaseCommand.h"

class ModuloCommand : public BaseCommand
{
	public:
		void execute(VirtualMachine& vm, vector<string>& parameters);
};