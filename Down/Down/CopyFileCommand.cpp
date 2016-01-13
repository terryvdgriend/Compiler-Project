#include "stdafx.h"
#include "CopyFileCommand.h"
#include "MandatoryCommandIncludes.h"
#ifdef _WIN32
#include "dirent.h"
#else
#include <dirent.h>
#endif

CopyFileCommand::CopyFileCommand()
{
}


CopyFileCommand::~CopyFileCommand()
{
}

void CopyFileCommand::execute(VirtualMachine & vm, AbstractFunctionCall & node)
{
    auto supergeheimeToken = node.getToken();
	vector<string>& parameters = node.getContentArrayNonConstant();
	auto variable1 = vm.getVariable(parameters[1]);
	auto variable2 = vm.getVariable(parameters[2]);
	if (variable1 != nullptr) {
		if (variable2 != nullptr) {
			if (variable1->getTokenType() == IToken::TYPE_TEXT && variable2->getTokenType() == IToken::TYPE_TEXT) {
				string file = variable1->getValue();
				string newDirectory = variable2->getValue();

				string filename = file;

				size_t last_slash_idx;

				#ifdef _WIN32
					last_slash_idx = filename.find_last_of("\\\\");
				#else
					last_slash_idx = filename.find_last_of("\\/");
				#endif

				if (std::string::npos != last_slash_idx)
				{
					filename.erase(0, last_slash_idx + 1);
				}

				file.erase(remove(file.begin(), file.end(), '\"'), file.end());
				newDirectory.erase(remove(newDirectory.begin(), newDirectory.end(), '\"'), newDirectory.end());
				filename.erase(remove(filename.begin(), filename.end(), '\"'), filename.end());

				DIR *dir;

				dir = opendir(newDirectory.c_str()); /*your directory*/
				if (dir == nullptr) {
					throwCustomError("Can not open: " + newDirectory, vm, supergeheimeToken);
					return;
				}

				dir = opendir(file.c_str()); /*your directory*/
				if (dir != nullptr) {
					throwCustomError(file + " is a directory", vm, supergeheimeToken);
					return;
				}

				#ifdef _WIN32
					if (newDirectory.back() != '\\') {
						newDirectory += "\\";
					}
				#else
					if (newDirectory.back() != '\/') {
						newDirectory += "\/";
					}
				#endif

				string newFile = newDirectory + filename;

				ifstream  src(file, ios::binary);
				if (!src.good()) {
					throwCustomError("Can not open file for copying", vm, supergeheimeToken);
					return;
				}
				ifstream  check(newFile, ios::binary);
				if (check.good()) {
					throwCustomError("File already exists in this map", vm, supergeheimeToken);
					return;
				}
				check.close();
				ofstream  dst(newFile, ios::binary);
				if (!dst.good()) {
					throwCustomError("Could not write file", vm, supergeheimeToken);
					return;
				}

				dst << src.rdbuf();
				src.close();
				dst.close();
				return;
			}
			throwCustomError("Parameters must be of type text.", vm);
			return;
		}
	}
	throwCustomError("Can't find ", vm);
}

pair<string, string> CopyFileCommand::accept(CommandVisitor & cmdVisitor)
{
	return cmdVisitor.visit(*this);
}