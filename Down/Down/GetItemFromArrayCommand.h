#pragma once
#include "BaseCommand.h"

class GetItemFromArrayCommand : public BaseCommand
{
public:
	void execute(VirtualMachine& vm, vector<string>& parameters);
};

