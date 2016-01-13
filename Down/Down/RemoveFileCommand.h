#pragma once
#include "BaseCommand.h"
class RemoveFileCommand: 
	public BaseCommand
{
public:
	RemoveFileCommand();
	~RemoveFileCommand();
	// Inherited via BaseCommand
	virtual void execute(VirtualMachine & vm, AbstractFunctionCall & node) override;
	virtual pair<string, string> accept(CommandVisitor & cmdVisitor) override;
};

