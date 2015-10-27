#pragma once
#include "BaseCommand.h"

class GetFromValueCommand : public BaseCommand
{
	public:
		GetFromValueCommand();
		~GetFromValueCommand();
		void execute(VirtualMachine *vm, vector<string> *parameters);
};