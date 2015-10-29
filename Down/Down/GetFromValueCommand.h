#pragma once
#include "BaseCommand.h"

class GetFromValueCommand : public BaseCommand
{
	public:
		void execute(VirtualMachine& vm, vector<string>& parameters);
};