#pragma once
#include "BaseCommand.h"

class ShowFunctionCommand : public BaseCommand
{
	public:
		void execute(VirtualMachine& vm, vector<string>& parameters);
};