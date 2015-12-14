#pragma once
#include "BaseCommand.h"
#include <iostream>
#include <io.h>
#include <time.h>
class GetAllFilesInDirectoryCommand :
	public BaseCommand
{
public:
	GetAllFilesInDirectoryCommand();
	~GetAllFilesInDirectoryCommand();

	// Inherited via BaseCommand
	virtual void execute(VirtualMachine & vm, AbstractFunctionCall & node) override;
	virtual pair<string, string> accept(CommandVisitor & cmdVisitor) override;
	void DumpEntry(_finddata_t & data);
	string Chop(string & str);
};

