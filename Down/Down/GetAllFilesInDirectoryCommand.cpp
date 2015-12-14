#include "stdafx.h"
#include "GetAllFilesInDirectoryCommand.h"
#include "CommandVisitor.h"

#ifdef _WIN32
    #include "dirent.h"
#else
    #include <dirent.h>
#endif


GetAllFilesInDirectoryCommand::GetAllFilesInDirectoryCommand()
{
}


GetAllFilesInDirectoryCommand::~GetAllFilesInDirectoryCommand()
{
}

void GetAllFilesInDirectoryCommand::execute(VirtualMachine & vm, AbstractFunctionCall & node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();
	auto var = *vm.getVariable(parameters[1]);

	string extension = "*.*";
	std::vector<string> out;
	DIR *dir;
	struct dirent *de;

	string directory = var.getValue();
	directory = directory.substr(1, directory.size() - 2);

	dir = opendir(directory.c_str()); /*your directory*/
	if (dir != nullptr) {
		while (dir)
		{
			de = readdir(dir);
			if (!de) break;
			Text::PrintLine(de->d_name);
		}
		closedir(dir);
	}
	else {
		throwTypeError(var, var, vm);
	}
	


}

pair<string, string> GetAllFilesInDirectoryCommand::accept(CommandVisitor & cmdVisitor)
{
	return cmdVisitor.visit(*this);
}

