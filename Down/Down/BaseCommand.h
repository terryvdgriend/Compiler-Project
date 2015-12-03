#pragma once

class VirtualMachine;
class Variable;

class BaseCommand
{
	public:
		virtual void execute(VirtualMachine& vm, vector<string>& parameters) = 0;
		virtual pair<string, string> accept(class CommandVisitor& cmdVisitor) = 0;
		bool isUndefined(Variable& var1, Variable& var2, VirtualMachine& vm);
		void throwTypeError(Variable& var1, Variable& var2, VirtualMachine& vm);
};