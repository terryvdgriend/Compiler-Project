#pragma once
#include "BaseCommand.h"
class MoveFilesCommand :
	public BaseCommand
{
public:
	MoveFilesCommand();
	~MoveFilesCommand();

	// Inherited via BaseCommand
	virtual void execute(VirtualMachine & vm, AbstractFunctionCall & node) override;
	virtual pair<string, string> accept(CommandVisitor & cmdVisitor) override;
};

