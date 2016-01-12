#pragma once
#include "BaseCommand.h"
class RemoveFilesCommand :
	public BaseCommand
{
public:
	RemoveFilesCommand();
	~RemoveFilesCommand();
	// Inherited via BaseCommand
	virtual void execute(VirtualMachine & vm, AbstractFunctionCall & node) override;
	virtual pair<string, string> accept(CommandVisitor & cmdVisitor) override;
};

