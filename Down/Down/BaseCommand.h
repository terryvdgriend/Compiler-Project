#pragma once
#include "VirtualMachine.h"
#include "ErrorHandler.h"
#include "Error.h"

using namespace std;

class BaseCommand
{
public:
	virtual void execute(VirtualMachine& vm, vector<string>& parameters) = 0;
	//virtual int execute(VirtualMachine& vm, vector<string>& parameters) = 0;
	virtual pair<string, string> accept(class CommandVisitor &cmdVisitor) = 0;
	bool isUndefined(Variable& var1, Variable& var2, VirtualMachine& vm);
	void throwTypeError(Variable& var1, Variable& var2, VirtualMachine& vm);
};