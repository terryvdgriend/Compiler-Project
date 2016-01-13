#pragma once
#include "BaseCommand.h"

class RemoveDirectoryCommand : public BaseCommand
{
	public:
		virtual void execute(VirtualMachine& vm, AbstractFunctionCall& node);
		virtual pair<string, string> accept(CommandVisitor& cmdVisitor);

	private:
		int UnixRemoveDirectoryRecursive(const char* dirname);
		string getExtension(const string fileName);
};