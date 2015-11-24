#pragma once
#include "BaseCommand.h"

class ShowFunctionCommand : public BaseCommand
{
	public:
		void execute(VirtualMachine& vm, vector<string>& parameters);
};

class ShowUpFunctionCommand : public BaseCommand
{
public:
	void execute(VirtualMachine& vm, vector<string>& parameters);
		// pair<string, string> accept(class CommandVisitor &cmdVisitor);
};