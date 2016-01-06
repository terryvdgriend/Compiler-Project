#pragma once
#include "BaseCommand.h"
class RenameFileCommand :
	public BaseCommand
{
public:
	RenameFileCommand();
	~RenameFileCommand();

	// Inherited via BaseCommand
	virtual void execute(VirtualMachine & vm, AbstractFunctionCall & node) override;
	virtual pair<string, string> accept(CommandVisitor & cmdVisitor) override;
private:
	string getExtension(const string fileName);
};

