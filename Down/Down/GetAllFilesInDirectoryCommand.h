#pragma once
#include "BaseCommand.h"
class GetAllFilesInDirectoryCommand :
	public BaseCommand
{
public:
	GetAllFilesInDirectoryCommand();
	~GetAllFilesInDirectoryCommand();

	// Inherited via BaseCommand
	virtual void execute(VirtualMachine & vm, AbstractFunctionCall & node) override;
	virtual pair<string, string> accept(CommandVisitor & cmdVisitor) override;
};

