#pragma once
#include "BaseCommand.h"

class TimesCommand : public BaseCommand
{
	public:
		void execute(VirtualMachine& vm, vector<string>& parameters);
};