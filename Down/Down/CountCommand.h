#pragma once
#include "BaseCommand.h"
class CountCommand :
	public BaseCommand
{
public:
	CountCommand();
	~CountCommand();

	// Inherited via BaseCommand
	virtual void execute(VirtualMachine & vm, AbstractFunctionCall & node) override;
	virtual pair<string, string> accept(CommandVisitor & cmdVisitor) override;
};

