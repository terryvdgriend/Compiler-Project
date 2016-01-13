#include "stdafx.h"
#include "RemoveDirectoryCommand.h"
#include "MandatoryCommandIncludes.h"

#ifdef _WIN32
	#include "dirent.h"
	#include <experimental/filesystem>

	namespace fs = experimental::filesystem;
#else
	#include <dirent.h>
#endif

void RemoveDirectoryCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();
	string file = vm.getVariable(parameters[1])->getValue();
	file.erase(remove(file.begin(), file.end(), '\"'), file.end());

	if (getExtension(file) != "") 
	{
        shared_ptr<Token> tempToken = node.getToken();
		throwCustomError("Cannot remove files, only directories (use removeFile to delete a file)", vm, tempToken);

		return;
	}
	int result = -1;

	#ifdef _WIN32
		if (fs::exists(file.c_str()))
		{
			fs::remove_all(file.c_str());
			result = 0;
		}
	#else
		result = RemoveDirectoryRecursiveUnix(file.c_str());
	#endif

	if (result == 0) 
	{
		cout << "Directory " << file << " and its contents were removed." << endl;
	}
	else 
	{
		char buff[256];
        
        #ifdef _WIN32
            strerror_s(buff, 100, errno);
        #else
            strerror_r(100, buff, errno);
        #endif
                
        shared_ptr<Token> tempToken = node.getToken();
		throwCustomError("Error: " + file + ": " + buff, vm, tempToken);
	}
}

pair<string, string> RemoveDirectoryCommand::accept(CommandVisitor& cmdVisitor)
{
	return cmdVisitor.visit(*this);
}

#ifndef _WIN32 // Intended for Unix based platforms
	int RemoveDirectoryCommand::UnixRemoveDirectoryRecursive(const char* dirname)
	{
		DIR* dir;
		struct dirent* entry;
		char path[PATH_MAX];

		if (path == NULL)
		{
			fprintf(stderr, "Out of memory error\n");

			return 0;
		}
		dir = opendir(dirname);

		if (dir == NULL)
		{
			perror("Error opendir()");

			return 0;
		}

		while ((entry = readdir(dir)) != NULL)
		{
			if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, ".."))
			{
				snprintf(path, (size_t)PATH_MAX, "%s/%s", dirname, entry->d_name);

				if (entry->d_type == DT_DIR)
				{
					UnixRemoveDirectoryRecursive(path);
				}
				remove(path);
			}
		}
		closedir(dir);

		int result = -1;
		char buff[256];

		result = rmdir(dirname);
		strerror_r(100, buff, errno);

		return result;
	}
#endif

string RemoveDirectoryCommand::getExtension(const string filename)
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