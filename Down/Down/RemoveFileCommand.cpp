#include "stdafx.h"
#include "RemoveFileCommand.h"
#include "MandatoryCommandIncludes.h"

#ifdef _WIN32
#include "dirent.h"
#else
#include <dirent.h>
#endif

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
	if (variable1 != nullptr) {
		if (variable1->getTokenType() == IToken::TYPE_TEXT) {
			string file = vm.getVariable(parameters[1])->getValue();
			file.erase(remove(file.begin(), file.end(), '\"'), file.end());

			if (opendir(file.c_str()) != nullptr){
				throwCustomError("Cannot remove directories (use removeDirectory to delete directories)", vm,node.getToken());
				return;
			}
			int result = remove(file.c_str());
			if (result != 0) {
				char buff[256];
                
                #ifdef _WIN32
                    strerror_s(buff, 100, errno);
                #else
                    strerror_r(100,buff, errno);
                #endif

				throwCustomError("Error: " + file + ": " + buff, vm, node.getToken());
			}
		}
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
