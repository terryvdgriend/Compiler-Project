#pragma once
#include "BaseCommand.h"

class ShowFunctionCommand : public BaseCommand
{
	public:
		void execute(VirtualMachine& vm, vector<string>& parameters);
		virtual pair<string, string> accept(CommandVisitor & cmdVisitor) override;
};

class ShowUpFunctionCommand : public BaseCommand
{
	public:
		void execute(VirtualMachine& vm, vector<string>& parameters);
		pair<string, string> accept(class CommandVisitor &cmdVisitor);
};

class RandomFunctionCommand : public BaseCommand
{
public:
	void execute(VirtualMachine& vm, vector<string>& parameters);
	pair<string, string> accept(class CommandVisitor &cmdVisitor);
};