#pragma once
#include "BaseCommand.h"

class AddLengthToArrayCommand : public BaseCommand
{
public:
	/*virtual*/ pair<string, string> accept(class CommandVisitor &cmdVisitor);

	// Inherited via BaseCommand
	virtual void execute(VirtualMachine & vm, AbstractFunctionCall & node) override;
};

