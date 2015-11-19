#pragma once
#include "BaseCommand.h"

class AddLengthToArrayCommand : public BaseCommand
{
public:
	void execute(VirtualMachine& vm, vector<string>& parameters);
};

