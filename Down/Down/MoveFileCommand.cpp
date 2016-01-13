#include "stdafx.h"
#include "MoveFileCommand.h"
#include "MandatoryCommandIncludes.h"

#ifdef _WIN32
	#include "dirent.h"
#else
	#include <dirent.h>
#endif

void MoveFileCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
    auto supergeheimeToken = node.getToken();
	vector<string>& parameters = node.getContentArrayNonConstant();
	auto variable1 = vm.getVariable(parameters[1]);
	auto variable2 = vm.getVariable(parameters[2]);

	if (variable1 != nullptr) 
	{
		if (variable2 != nullptr) 
		{
			if (variable1->getTokenType() == IToken::TYPE_TEXT && variable2->getTokenType() == IToken::TYPE_TEXT) 
			{
				string file = variable1->getValue();
				string newDirectory = variable2->getValue();

				string filename = file;

				size_t last_slash_idx; 

				#ifdef _WIN32
					last_slash_idx = filename.find_last_of("\\\\");
				#else
					last_slash_idx = filename.find_last_of("\\/");
				#endif

				if (string::npos != last_slash_idx)
				{
					filename.erase(0, last_slash_idx + 1);
				}
				file.erase(remove(file.begin(), file.end(), '\"'), file.end());
				newDirectory.erase(remove(newDirectory.begin(), newDirectory.end(), '\"'), newDirectory.end());
				filename.erase(remove(filename.begin(), filename.end(), '\"'), filename.end());
								
				DIR* dir = opendir(newDirectory.c_str()); /*your directory*/

				if (dir == nullptr)
				{
					//dir is null dir not found
					throwCustomError("Directory not found! Cannot move file..", vm, supergeheimeToken);

					return;
				}
				closedir(dir);
				dir = opendir(file.c_str()); /*your directory*/

				if (dir != nullptr) 
				{
					//dir is null dir not found
					throwCustomError("Directory not found! Cannot move file..", vm, supergeheimeToken);
					closedir(dir);

					return;
				}
				closedir(dir);

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
				int result = rename(file.c_str(), "");

				if (result == 0) 
				{
					cout << "File " << file << " moved to " << newFile << endl;
				}
				else 
				{
					cout << "Error moving file! Code: " << result << endl;
					char buff[256];

					#ifdef _WIN32
						strerror_s(buff, 100, errno);
					#else
						strerror_r(100, buff, errno);
					#endif
					
					throwCustomError(buff, vm,node.getToken());

					return;
				}

				return;
			}
			throwCustomError("Parameters must be of type text.", vm, supergeheimeToken);

			return;
		}
	}
	throwCustomError("Can't find ", vm, supergeheimeToken);
}

pair<string, string> MoveFileCommand::accept(CommandVisitor& cmdVisitor)
{
	return cmdVisitor.visit(*this);
}