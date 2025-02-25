#pragma once
#include "BaseCommand.h"
class CopyFiles :
	public BaseCommand
{
public:
	CopyFiles();
	~CopyFiles();
	// Inherited via BaseCommand
	virtual void execute(VirtualMachine & vm, AbstractFunctionCall & node) override;
	virtual pair<string, string> accept(CommandVisitor & cmdVisitor) override;
};

