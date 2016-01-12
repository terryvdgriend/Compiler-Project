#pragma once
#include "BaseCommand.h"
class AndCommand :
	public BaseCommand
{
public:
	AndCommand();
	~AndCommand();

	// Inherited via BaseCommand
	virtual void execute(VirtualMachine & vm, AbstractFunctionCall & node) override;
	virtual pair<string, string> accept(CommandVisitor & cmdVisitor) override;
};

