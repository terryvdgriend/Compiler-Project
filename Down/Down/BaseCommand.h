#pragma once
#include "VirtualMachine.h"

class BaseCommand
{
	public:
		virtual void execute(VirtualMachine *vm, vector<string> *parameters) = 0;
};