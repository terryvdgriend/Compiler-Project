#pragma once
#include "BaseCommand.h"
class ParseIntCommand :
	public BaseCommand
{
public:
	ParseIntCommand();
	~ParseIntCommand();

	// Inherited via BaseCommand
	virtual void execute(VirtualMachine & vm, AbstractFunctionCall & node) override;
	bool is_number(const string & s);
	virtual pair<string, string> accept(CommandVisitor & cmdVisitor) override;
};

