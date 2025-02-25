#include "stdafx.h"
#include "MoveFilesCommand.h"
#include "MandatoryCommandIncludes.h"

#ifdef _WIN32
	#include "dirent.h"
#else
	#include <dirent.h>
#endif

void MoveFilesCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
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
						//dir is null dir not found
						throwCustomError("Directory not found! Cannot move files..", vm, supergeheimeToken);

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

						dir = opendir(file.c_str()); /*your directory*/

						if (dir != nullptr) 
						{
							//dir is null dir not found
							throwCustomError("Directory not found! Cannot move files..", vm, supergeheimeToken);
							closedir(dir);

							return;
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

						int result = rename(file.c_str(), newFile.c_str());

						if (result == 0) 
						{
							cout << "File " << file << " move to " << newFile << endl;
						}
						else 
						{
							char buff[256];

							#ifdef _WIN32
								strerror_s(buff, 100, errno);
							#else
								strerror_r(100, buff, errno);
							#endif
							errors.push_back("File " + file + " has an error: " + buff);
						}
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

pair<string, string> MoveFilesCommand::accept(CommandVisitor& cmdVisitor)
{
	return cmdVisitor.visit(*this);
}