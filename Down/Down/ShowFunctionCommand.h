#pragma once
#include "BaseCommand.h"

class ShowFunctionCommand : public BaseCommand
{
	public:
		ShowFunctionCommand();
		~ShowFunctionCommand();
		void execute(VirtualMachine *vm, vector<string> *parameters);
};