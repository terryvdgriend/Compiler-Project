#include "stdafx.h"
#include "GetAllFilesInDirectoryCommand.h"
#include "MandatoryCommandIncludes.h"
#include "CompileSingleStatement.h"

#ifdef _WIN32
    #include "dirent.h"
#else
    #include <dirent.h>
#endif

void GetAllFilesInDirectoryCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();
	auto var = vm.getVariable(parameters[1]);
	string extension = "*.*";
	vector<string> out;
	DIR* dir = nullptr;
	struct dirent* dirent = nullptr;

	string directory = var->getValue();
	directory = directory.substr(1, directory.size() - 2);

	dir = opendir(directory.c_str()); // Target directory

	if (dir == nullptr) 
	{
		//throwTypeError(*var, *var, vm);
		//dir is null dir not found
		throwCustomError("Directory not found! Cannot get all files in directory..", vm, node.getToken());
		return;
	}

	while (dir)
	{
		dirent = readdir(dir);

		if (!dirent)
		{
			break;
		}
		string direct = dirent->d_name;
		direct = directory + "\\" + direct;
		DIR* temp = opendir(direct.c_str());

		if (!temp) 
		{
			string fileName = dirent->d_name;
			out.push_back("\"" + fileName + "\"");
		}
		closedir(temp);
	}
	closedir(dir);
	
	string buffer;
	CompileSingleStatement varGetter = CompileSingleStatement();
	string localVariable;
	string arrayDictionary = varGetter.getNextLocalVariableName(buffer);
	string arrayIdentifier = varGetter.getNextLocalVariableName(buffer);

	vm.setVariable(arrayDictionary, "", IToken::TYPE_TEXT_ARRAY);
	shared_ptr<Variable> arrayVar = vm.getVariable(arrayDictionary);

	vm.setFunctionParameter(arrayDictionary, arrayIdentifier);
	int Size = out.size();
	vm.addArrayToDictionary(arrayDictionary, vector<int>({ Size }));
	vm.addIdentifer(arrayIdentifier);

	for (size_t i = 0; i < out.size(); i++)
	{
		localVariable = varGetter.getNextLocalVariableName(buffer);
		vm.setVariable(localVariable, out.at(i), IToken::TYPE_TEXT);
		vm.addItemToVariableArrayAt(arrayDictionary, vector<string>({ to_string(i) }), vm.getVariable(localVariable));
	}
	vm.setReturnValue(arrayIdentifier);
	vm.setReturnToken(IToken::TYPE_TEXT_ARRAY);
}

pair<string, string> GetAllFilesInDirectoryCommand::accept(CommandVisitor& cmdVisitor)
{
	return cmdVisitor.visit(*this);
}