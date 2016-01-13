#include "stdafx.h"
#include "CopyFilesCommand.h"
#include "MandatoryCommandIncludes.h"

#ifdef _WIN32
	#include "dirent.h"
#else
	#include <dirent.h>
#endif

void CopyFilesCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
    auto supergeheimeToken = node.getToken();
	vector<string>& parameters = node.getContentArrayNonConstant();
	auto variable1 = vm.getVariable(parameters[1]);
	auto varArray = vm.getVariableArray(parameters.at(1));
	auto variable2 = vm.getVariable(parameters[2]);
	vector<string> errors;

	if (variable1 != nullptr) 
	{
		if (variable2 != nullptr) 
		{
			if (variable1->getTokenType() == IToken::TYPE_TEXT_ARRAY && variable2->getTokenType() == IToken::TYPE_TEXT) 
			{
				if (varArray != nullptr && varArray->variableArrayDictionary.size() > 0) 
				{
					string newDirectory = variable2->getValue();
					newDirectory.erase(remove(newDirectory.begin(), newDirectory.end(), '\"'), newDirectory.end());

					DIR* dir = opendir(newDirectory.c_str()); /*your directory*/

					if (dir == nullptr) 
					{
						throwCustomError("Can not open: " + newDirectory, vm, supergeheimeToken);

						return;
					}
					closedir(dir);

					for (auto fileInArray : varArray->variableArrayDictionary) 
					{
						string file = fileInArray->getValue();
						string filename = file;

						const size_t last_slash_idx = filename.find_last_of("\\/");

						if (string::npos != last_slash_idx)
						{
							filename.erase(0, last_slash_idx + 1);
						}
						file.erase(remove(file.begin(), file.end(), '\"'), file.end());
						filename.erase(remove(filename.begin(), filename.end(), '\"'), filename.end());

						dir = opendir(file.c_str());

						if (dir != nullptr) 
						{
							errors.push_back(file + " is a directory");

							continue;
						}
						closedir(dir);

						#ifdef _WIN32
							if (newDirectory.back() != '\\') 
							{
								newDirectory += "\\";
							}
						#else
							if (newDirectory.back() != '\/') 
							{
								newDirectory += "\/";
							}
						#endif

						string newFile = newDirectory + filename;
						bool hasError = false;
						ifstream src(file, ios::binary);

						if (!src.good()) 
						{
							errors.push_back("Can not open file for copying: " + file);
							hasError = true;
						}
						ifstream check(newFile, ios::binary);

						if (check.good() && !hasError)
						{
							errors.push_back("File already exists in this map: " + newFile);
							hasError = true;
						}
						check.close();
						ofstream dst(newFile, ios::binary);

						if (!dst.good() && !hasError) 
						{
							errors.push_back("Could not write file: " + newFile);
							hasError = true;
						}

						if (!hasError) 
						{
							dst << src.rdbuf();
						}
						src.close();
						dst.close();
					}

					for (auto err : errors) 
					{
						throwCustomError(err, vm, supergeheimeToken);
					}

					return;
				}
				throwCustomError("Array is empty.", vm, supergeheimeToken);

				return;
			}
			throwCustomError("Parameters must be of type text.", vm, supergeheimeToken);

			return;
		}
	}
	throwCustomError("Can't find ", vm, supergeheimeToken);
}

pair<string, string> CopyFilesCommand::accept(CommandVisitor& cmdVisitor)
{
	return cmdVisitor.visit(*this);
}