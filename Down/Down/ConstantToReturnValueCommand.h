#pragma once
#include "BaseCommand.h"

class ConstantToReturnValueCommand : public BaseCommand
{
	public:
		void execute(VirtualMachine& vm, vector<string>& parameters);
};