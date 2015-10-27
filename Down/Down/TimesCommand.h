#pragma once
#include "BaseCommand.h"

class TimesCommand : public BaseCommand
{
	public:
		TimesCommand();
		~TimesCommand();
		void execute(VirtualMachine *vm, vector<string> *parameters);
};