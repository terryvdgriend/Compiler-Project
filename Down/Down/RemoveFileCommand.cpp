#include "stdafx.h"
#include "RemoveFileCommand.h"
#include "MandatoryCommandIncludes.h"
#include <cstdint>
#include <experimental/filesystem>


RemoveFileCommand::RemoveFileCommand()
{
}


RemoveFileCommand::~RemoveFileCommand()
{
}

void RemoveFileCommand::execute(VirtualMachine & vm, AbstractFunctionCall & node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();
	auto variable1 = vm.getVariable(parameters[1]);
	string file = vm.getVariable(parameters[1])->getValue();
	file.erase(remove(file.begin(), file.end(), '\"'), file.end());
	
	if (getExtension(file) == "") {
		throwCustomError("Missing file extension (use removeDirectory to delete directories)", vm);
		return;
	}
	int result = remove(file.c_str());
	if (result == 0) {
		cout << "File " << file << " removed."<< endl;
	}
	else {
		char buff[256];

		strerror_s(buff, 100, errno);
		throwCustomError("Error: " + file + ": " + buff, vm);
	}
}

string RemoveFileCommand::getExtension(const string filename)
{
	int pos;
	string ext;
	pos = filename.find_last_of('.');
	if (pos == -1) // There was no '.' in the file name
		return ""; // Return an empty string

	return filename.substr(pos, -1);
}

pair<string, string> RemoveFileCommand::accept(CommandVisitor & cmdVisitor)
{
	return cmdVisitor.visit(*this);
}
