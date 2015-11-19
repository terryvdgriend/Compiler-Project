#pragma once
#include "BaseCommand.h"

class AddItemToArrayCommand : public BaseCommand
{
public:
	void execute(VirtualMachine& vm, vector<string>& parameters);
};

