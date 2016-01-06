#include "stdafx.h"
#include "RenameFileCommand.h"
#include "MandatoryCommandIncludes.h"
#include <errno.h>
#include <stdio.h>


RenameFileCommand::RenameFileCommand()
{
}

RenameFileCommand::~RenameFileCommand()
{
}

void RenameFileCommand::execute(VirtualMachine & vm, AbstractFunctionCall & node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();
	auto variable1 = vm.getVariable(parameters[1]);
	auto variable2 = vm.getVariable(parameters[2]);
	string oldFile = vm.getVariable(parameters[1])->getValue();
	string newFile = vm.getVariable(parameters[2])->getValue();
	if (getExtension(oldFile) != getExtension(newFile)) {
		throwCustomError("Input does not have matching extensions", vm);
	}

	oldFile.erase(remove(oldFile.begin(), oldFile.end(), '\"'), oldFile.end());
	newFile.erase(remove(newFile.begin(), newFile.end(), '\"'), newFile.end());
	int result = rename(oldFile.c_str(), newFile.c_str());
	if (result == 0) {
		cout << "File " << oldFile << " renamed to " << newFile << endl;
	}
	else {
		cout << "Error renaming file! Code: " << result << endl;
		char buff[256];

		strerror_s(buff, 100, errno);
		std::cout << "Error: " << buff << std::endl;
	}
}

string RenameFileCommand::getExtension(const string filename)
{
	int pos;
	string ext;
	pos = filename.find_last_of('.');
	if (pos == -1) // There was no '.' in the file name
		return ""; // Return an empty string

	return filename.substr(pos, -1);
}

pair<string, string> RenameFileCommand::accept(CommandVisitor & cmdVisitor)
{
	return cmdVisitor.visit(*this);
}
