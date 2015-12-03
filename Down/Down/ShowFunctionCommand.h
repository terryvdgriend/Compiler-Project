#pragma once
#include "BaseCommand.h"

class ShowFunctionCommand : public BaseCommand
{
	public:
		void execute(VirtualMachine& vm, AbstractFunctionCall& node);
		virtual pair<string, string> accept(CommandVisitor & cmdVisitor) override;
};

class ShowUpFunctionCommand : public BaseCommand
{
	public:
		void execute(VirtualMachine& vm, AbstractFunctionCall& node);
		pair<string, string> accept(class CommandVisitor &cmdVisitor);
};

class RandomFunctionCommand : public BaseCommand
{
public:
	void execute(VirtualMachine& vm, AbstractFunctionCall& node);
	pair<string, string> accept(class CommandVisitor &cmdVisitor);
};