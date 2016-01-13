#pragma once
#include "BaseCommand.h"

class GetFilesInDirectoryByExtensionCommand : public BaseCommand
{
	public:
		void execute(VirtualMachine& vm, AbstractFunctionCall& node);
		pair<string, string> accept(CommandVisitor& cmdVisitor);

	private:
		string getExtension(const string fileName);
};