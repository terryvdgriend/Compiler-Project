#pragma once
#include "BaseCommand.h"
class OrCommand :
	public BaseCommand
{
public:
	OrCommand();
	~OrCommand();

	// Inherited via BaseCommand
	virtual void execute(VirtualMachine & vm, AbstractFunctionCall & node) override;
	virtual pair<string, string> accept(CommandVisitor & cmdVisitor) override;
};

