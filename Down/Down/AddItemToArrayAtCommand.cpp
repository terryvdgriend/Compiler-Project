#include "stdafx.h"
#include "AddItemToArrayAtCommand.h"
#include "CommandVisitor.h"

void AddItemToArrayAtCommand::execute(VirtualMachine& vm, vector<string>& parameters)
{
	// Add item to array
	// Parameters:
	// 1. Array name
	// 2. Array location
	// 3. Item value
}

pair<string, string> AddItemToArrayAtCommand::accept(CommandVisitor& commandVisitor) {
	return commandVisitor.visit(*this);
}