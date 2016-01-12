#include "stdafx.h"
#include "GetVideoFilesInDirectoryCommand.h"
#include "MandatoryCommandIncludes.h"
#include "CompileSingleStatement.h"

#ifdef _WIN32
#include "dirent.h"
#else
#include <dirent.h>
#endif


GetVideoFilesInDirectoryCommand::GetVideoFilesInDirectoryCommand()
{
}


GetVideoFilesInDirectoryCommand::~GetVideoFilesInDirectoryCommand()
{
}

void GetVideoFilesInDirectoryCommand::execute(VirtualMachine & vm, AbstractFunctionCall & node)
{
	// TODO: DO EXTENSION STUFF
	vector<string>& parameters = node.getContentArrayNonConstant();
	auto var = vm.getVariable(parameters[1]);

	// These 2 numbers must remain the same!
	int numberOfExtensions = 8;
	string extensions[8] = { ".flv", ".gif", ".avi", ".mov", ".wmv", ".mp4", ".mpg", ".m4v" };

	std::vector<string> out;
	DIR *dir;
	struct dirent *de;

	string directory = var->getValue();
	directory = directory.substr(1, directory.size() - 2);

	dir = opendir(directory.c_str()); /*your directory*/
	if (dir == nullptr) {
		throwTypeError(*var, *var, vm);
		return;
	}
	while (dir)
	{
		de = readdir(dir);
		if (!de) break;
		string extension = getExtension(de->d_name);
		for (int i = 0; i < 8; i++) {
			if (extension == extensions[i]) {
				out.push_back(de->d_name);
				break;
			}
		}
	}
	closedir(dir);

	string buffer;
	CompileSingleStatement varGetter = CompileSingleStatement();
	string localVariable;
	string arrayDictionary = varGetter.getNextLocalVariableName(buffer);
	string arrayIdentifier = varGetter.getNextLocalVariableName(buffer);
	vm.setVariable(arrayDictionary, "", IToken::TYPE_TEXT_ARRAY);
	auto arrayVar = vm.getVariable(arrayDictionary);
	vm.setFunctionParameter(arrayDictionary, arrayIdentifier);
	int size = out.size();
	vm.addArrayToDictionary(arrayDictionary, vector<int>({size}));
	vm.addIdentifer(arrayIdentifier);

	for (size_t i = 0; i < out.size(); i++)
	{
		localVariable = varGetter.getNextLocalVariableName(buffer);
		vm.setVariable(localVariable, out.at(i), IToken::TYPE_TEXT);
		cout << out.at(i) << endl;
		vm.addItemToVariableArrayAt(arrayDictionary, vector<string>({ to_string(i) }), vm.getVariable(localVariable));
	}
	vm.setReturnValue(arrayIdentifier);
	vm.setReturnToken(IToken::TYPE_TEXT_ARRAY);
}

string GetVideoFilesInDirectoryCommand::getExtension(const string filename)
{
	int pos;
	string ext;
	pos = filename.find_last_of('.');
	if (pos == -1) // There was no '.' in the file name
		return ""; // Return an empty string

	return filename.substr(pos, -1);
}


pair<string, string> GetVideoFilesInDirectoryCommand::accept(CommandVisitor & cmdVisitor)
{
	return cmdVisitor.visit(*this);
}

