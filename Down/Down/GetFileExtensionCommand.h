#pragma once
#include "BaseCommand.h"
class GetFileExtensionCommand :
	public BaseCommand
{
public:
	GetFileExtensionCommand();
	~GetFileExtensionCommand();

	// Inherited via BaseCommand
	virtual void execute(VirtualMachine & vm, AbstractFunctionCall & node) override;
	virtual pair<string, string> accept(CommandVisitor & cmdVisitor) override;
};

