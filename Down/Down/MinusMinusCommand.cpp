#include "stdafx.h"
#include "MinusMinusCommand.h"
#include "CommandVisitor.h"

void MinusMinusCommand::execute(VirtualMachine& vm, vector<string>& parameters)
{
	//Todo
}

std::pair<string, string> MinusMinusCommand::accept(CommandVisitor& commandVisitor) {
	return commandVisitor.visit(*this);
}