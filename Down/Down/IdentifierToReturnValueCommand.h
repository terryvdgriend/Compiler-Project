#pragma once
#include "BaseCommand.h"

class IdentifierToReturnValueCommand : public BaseCommand
{
	public:
		IdentifierToReturnValueCommand();
		~IdentifierToReturnValueCommand();
		void execute(VirtualMachine *vm, vector<string> *parameters);
};