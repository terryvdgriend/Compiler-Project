#include "stdafx.h"
#include "GetFilesInDirectoryByExtensionCommand.h"
#include "MandatoryCommandIncludes.h"
#include "CompileSingleStatement.h"

#ifdef _WIN32
	#include "dirent.h"
#else
	#include <dirent.h>
#endif

void GetFilesInDirectoryByExtensionCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
    auto supergeheimeToken = node.getToken();
	// TODO: DO EXTENSION STUFF
	vector<string>& parameters = node.getContentArrayNonConstant();
	auto var = vm.getVariable(parameters[1]);

	string extension = ".cpp";
	vector<string> out;
	DIR* dir;
	struct dirent* de;

	string directory = var->getValue();
	directory = directory.substr(1, directory.size() - 2);

	dir = opendir(directory.c_str()); /*your directory*/

	if (dir == nullptr) 
	{
		//dir is null dir not found
		throwCustomError("Directory not found! Cannot get files by extension..", vm, supergeheimeToken);

		return;
	}

	while (dir)
	{
		de = readdir(dir);

		if (!de) 
		{
			break;
		}

		if (getExtension(de->d_name) == extension) 
		{
			out.push_back(de->d_name);
		}
	}
	closedir(dir);

	string buffer;
	CompileSingleStatement varGetter = CompileSingleStatement();
	string localVariable;
	string arrayDictionary = varGetter.getNextLocalVariableName(buffer);
	string arrayIdentifier = varGetter.getNextLocalVariableName(buffer);
	vm.setVariable(arrayDictionary, "", supergeheimeToken, IToken::TYPE_TEXT_ARRAY);
	auto arrayVar = vm.getVariable(arrayDictionary);
	vm.setFunctionParameter(arrayDictionary, arrayIdentifier);
	int size = out.size();
	vm.addArrayToDictionary(arrayDictionary, vector<int>({size}));
	vm.addIdentifer(arrayIdentifier);

	for (size_t i = 0; i < out.size(); i++)
	{
		localVariable = varGetter.getNextLocalVariableName(buffer);
		vm.setVariable(localVariable, out.at(i), supergeheimeToken, IToken::TYPE_TEXT);
		cout << out.at(i) << endl;
		vm.addItemToVariableArrayAt(arrayDictionary, vector<string>({ to_string(i) }), vm.getVariable(localVariable));
	}
	vm.setReturnValue(arrayIdentifier);
	vm.setReturnToken(IToken::TYPE_TEXT_ARRAY);
}

pair<string, string> GetFilesInDirectoryByExtensionCommand::accept(CommandVisitor& cmdVisitor)
{
	return cmdVisitor.visit(*this);
}

string GetFilesInDirectoryByExtensionCommand::getExtension(const string filename)
{
	int pos;
	string ext;
	pos = filename.find_last_of('.');

	if (pos == -1) // There was no '.' in the file name
	{
		return ""; // Return an empty string
	}

	return filename.substr(pos, -1);
}