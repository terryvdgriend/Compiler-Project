#pragma once
#include "BaseCommand.h"
class RemoveDirectoryCommand :
	public BaseCommand
{
public:
	RemoveDirectoryCommand();
	~RemoveDirectoryCommand();
	virtual void execute(VirtualMachine & vm, AbstractFunctionCall & node) override;
	virtual pair<string, string> accept(CommandVisitor & cmdVisitor) override;
	int RemoveDirectoryRecursiveUnix(const char *dirname);
private:
	string getExtension(const string fileName);
};

