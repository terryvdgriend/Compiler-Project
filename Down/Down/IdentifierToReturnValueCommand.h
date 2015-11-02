#pragma once
#include "BaseCommand.h"

class IdentifierToReturnValueCommand : public BaseCommand
{
	public:;
		   void execute(VirtualMachine& vm, vector<string>& parameters);
};