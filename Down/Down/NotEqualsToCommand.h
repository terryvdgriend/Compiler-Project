#pragma once
#include "BaseCommand.h"

class NotEqualsToCommand : public BaseCommand
{
	public:
		NotEqualsToCommand();
		~NotEqualsToCommand();
		void execute(VirtualMachine *vm, vector<string> *parameters);
};