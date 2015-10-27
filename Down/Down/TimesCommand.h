#pragma once
#include "BaseCommand.h"

class TimesCommand : public BaseCommand
{
	public:
		~TimesCommand();
		void execute(VirtualMachine *vm, vector<string> *parameters);
};