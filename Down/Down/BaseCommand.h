#pragma once
#include "VirtualMachine.h"

using namespace std;

class BaseCommand
{
public:
	virtual void execute(VirtualMachine& vm, vector<string>& parameters) = 0;
	virtual pair<string, string> accept(class CommandVisitor &cmdVisitor) = 0;
};