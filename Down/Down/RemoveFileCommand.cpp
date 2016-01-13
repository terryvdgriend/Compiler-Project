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
    auto supergeheimeToken = node.getToken();
	vector<string>& parameters = node.getContentArrayNonConstant();
	auto variable1 = vm.getVariable(parameters[1]);
	if (variable1 != nullptr) {
		if (variable1->getTokenType() == IToken::TYPE_TEXT) {
			string file = vm.getVariable(parameters[1])->getValue();
			file.erase(remove(file.begin(), file.end(), '\"'), file.end());

			if (opendir(file.c_str()) != nullptr){
				throwCustomError("Cannot remove directories (use removeDirectory to delete directories)", vm,supergeheimeToken);
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

				throwCustomError("Error: " + file + ": " + buff, vm, supergeheimeToken);
			}
			return;
		}
		else {
			throwCustomError("Parameters must be of type text.", vm, node.getToken());
			return;
		}
	}
	throwCustomError("Can't find ", vm, node.getToken());
}

pair<string, string> RemoveFileCommand::accept(CommandVisitor & cmdVisitor)
{
	return cmdVisitor.visit(*this);
}
