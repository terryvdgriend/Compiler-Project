#pragma once
#include "BaseCommand.h"

class ConstantToReturnValueCommand : public BaseCommand
{
	public:
		ConstantToReturnValueCommand();
		~ConstantToReturnValueCommand();
		void execute(VirtualMachine *vm, vector<string> *parameters);
};