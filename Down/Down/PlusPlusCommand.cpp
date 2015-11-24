#include "stdafx.h"
#include "PlusPlusCommand.h"
#include "CommandVisitor.h"

void PlusPlusCommand::execute(VirtualMachine& vm, vector<string>& parameters)
{
	//Todo
}

std::pair<string, string> PlusPlusCommand::accept(CommandVisitor& commandVisitor) {
	return commandVisitor.visit(*this);
}