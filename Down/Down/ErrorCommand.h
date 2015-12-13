#pragma once
#include "BaseCommand.h"


class ErrorCommand :public BaseCommand
{
public:
	void execute(VirtualMachine& vm, AbstractFunctionCall& node);
	virtual pair<string, string> accept(CommandVisitor & cmdVisitor) override;
};
