#include "stdafx.h"
#include "RenameFileCommand.h"
#include "MandatoryCommandIncludes.h"
#include <errno.h>
#include <stdio.h>

#ifdef _WIN32
#include "dirent.h"
#else
#include <dirent.h>
#endif


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
	if (variable1 != nullptr) {
		if (variable2 != nullptr) {
			if (variable1->getTokenType() == IToken::TYPE_TEXT && variable2->getTokenType() == IToken::TYPE_TEXT) {
				string oldFile = vm.getVariable(parameters[1])->getValue();
				string newFile = vm.getVariable(parameters[2])->getValue();
				if (getExtension(oldFile) != getExtension(newFile)) {
					throwCustomError("Input does not have matching extensions", vm, node.getToken());
				}

				newFile.erase(remove(newFile.begin(), newFile.end(), '\"'), newFile.end());

				vector<char> forbidden = vector<char>({ '<', '>', ':', '\"', '\/', '\\', '|' , '?', '*' });
				for (char& c : newFile) {
					for (int i = 0; i < forbidden.size(); i++) {
						if (forbidden.at(i) == c) {
							// Because appending characters to the end of strings is just ugly :/
							string error = "Invalid character: ";
							throwCustomError(error += c, vm);
							return;
						}
					}
				}

				oldFile.erase(remove(oldFile.begin(), oldFile.end(), '\"'), oldFile.end());

				DIR *dir;
				dir = opendir(oldFile.c_str());

				if (dir != nullptr) {
					throwCustomError("Cannot rename directories", vm, node.getToken());
					return;
				}

				int pos;
				#ifdef _WIN32
								pos = oldFile.find_last_of('\\\\');
				#else
								pos = oldFile.find_last_of('\\/');
				#endif
				if (pos == -1) {
					throwCustomError("Incorrect input: is the first parameter a full path?", vm, node.getToken());
					return;
				}

				newFile = oldFile.substr(0, pos + 1) + newFile;

				int result = rename(oldFile.c_str(), newFile.c_str());
				if (result != 0) {
					cout << "Error renaming file! Code: " << result << endl;
					char buff[256];

					#ifdef _WIN32
						strerror_s(buff, 100, errno);
					#else
						strerror_r(100, buff, errno);
					#endif

					throwCustomError(buff, vm);
				}
				return;
			}
			else {
				throwCustomError("Parameters must be of type 'text'", vm, node.getToken());
				return;
			}
		}
	}
	throwCustomError("Parameters not set", vm, node.getToken());
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
