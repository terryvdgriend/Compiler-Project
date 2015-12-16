#pragma once
#include "AbstractFunctionCall.h"

class CommandVisitor;
class VirtualMachine;
class Variable;

class BaseCommand
{
	public:
		virtual void execute(VirtualMachine& vm, AbstractFunctionCall& node) = 0;
		virtual pair<string, string> accept(CommandVisitor& cmdVisitor) = 0;
		bool isUndefined(Variable& var1, Variable& var2, VirtualMachine& vm);
		void throwTypeError(Variable& var1, Variable& var2, VirtualMachine& vm);
		void throwCustomError(string error, VirtualMachine & vm);
};