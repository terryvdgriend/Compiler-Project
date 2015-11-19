#pragma once
#include "BaseCommand.h"

class AddArrayToDictionary : public BaseCommand
{
public:
	void execute(VirtualMachine& vm, vector<string>& parameters);
};