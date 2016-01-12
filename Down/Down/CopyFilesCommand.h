#pragma once
#include "BaseCommand.h"
class CopyFilesCommand :
	public BaseCommand
{
public:
	CopyFilesCommand();
	~CopyFilesCommand();
	// Inherited via BaseCommand
	virtual void execute(VirtualMachine & vm, AbstractFunctionCall & node) override;
	virtual pair<string, string> accept(CommandVisitor & cmdVisitor) override;
};

