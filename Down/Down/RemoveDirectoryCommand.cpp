#include "stdafx.h"
#include "RemoveDirectoryCommand.h"
#include "MandatoryCommandIncludes.h"

// OPLOSSEN DAT WIN32 NIET MEER NODIG IS, OSX STAAT ONDERAAN NU

#ifdef _WIN32
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;


RemoveDirectoryCommand::RemoveDirectoryCommand()
{
}


RemoveDirectoryCommand::~RemoveDirectoryCommand()
{
}

void RemoveDirectoryCommand::execute(VirtualMachine & vm, AbstractFunctionCall & node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();
	auto variable1 = vm.getVariable(parameters[1]);
	string file = vm.getVariable(parameters[1])->getValue();
	file.erase(remove(file.begin(), file.end(), '\"'), file.end());

	if (getExtension(file) != "") {
		throwCustomError("Cannot remove files, only directories (use removeFile to delete a file)", vm, node.getToken());
		return;
	}
	int result = fs::remove_all(file.c_str());
	if (result == 1) {
		cout << "Directory " << file << " and its contents were removed." << endl;
	}
	else {
		char buff[256];

		strerror_s(buff, 100, errno);
		throwCustomError("Error: " + file + ": " + buff, vm, node.getToken());
	}
}

string RemoveDirectoryCommand::getExtension(const string filename)
{
	int pos;
	string ext;
	pos = filename.find_last_of('.');
	if (pos == -1) // There was no '.' in the file name
		return ""; // Return an empty string

	return filename.substr(pos, -1);
}

pair<string, string> RemoveDirectoryCommand::accept(CommandVisitor & cmdVisitor)
{
	return cmdVisitor.visit(*this);
}






#else // OSX


RemoveDirectoryCommand::RemoveDirectoryCommand()
{
}


RemoveDirectoryCommand::~RemoveDirectoryCommand()
{
}

void RemoveDirectoryCommand::execute(VirtualMachine & vm, AbstractFunctionCall & node)
{

}

string RemoveDirectoryCommand::getExtension(const string filename)
{
    return "";
}

pair<string, string> RemoveDirectoryCommand::accept(CommandVisitor & cmdVisitor)
{
    return cmdVisitor.visit(*this);
}


#endif