#pragma once
#include "BaseCommand.h"
class CopyFileCommand :
	public BaseCommand
{
public:
	CopyFileCommand();
	~CopyFileCommand();
	// Inherited via BaseCommand
	virtual void execute(VirtualMachine & vm, AbstractFunctionCall & node) override;
	virtual pair<string, string> accept(CommandVisitor & cmdVisitor) override;
};

