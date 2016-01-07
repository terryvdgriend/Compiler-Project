#pragma once
#include "BaseCommand.h"
class MoveFileCommand :
	public BaseCommand
{
public:
	MoveFileCommand();
	~MoveFileCommand();

	// Inherited via BaseCommand
	virtual void execute(VirtualMachine & vm, AbstractFunctionCall & node) override;
	virtual pair<string, string> accept(CommandVisitor & cmdVisitor) override;
};

