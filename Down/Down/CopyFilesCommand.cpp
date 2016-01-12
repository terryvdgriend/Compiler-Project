#include "stdafx.h"
#include "CopyFilesCommand.h"
#include "MandatoryCommandIncludes.h"
#ifdef _WIN32
#include "dirent.h"
#else
#include <dirent.h>
#endif

CopyFilesCommand::CopyFilesCommand()
{
}


CopyFilesCommand::~CopyFilesCommand()
{
}

void CopyFilesCommand::execute(VirtualMachine & vm, AbstractFunctionCall & node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();
	auto variable1 = vm.getVariable(parameters[1]);
	auto varArray = vm.getVariableArray(parameters.at(1));
	auto variable2 = vm.getVariable(parameters[2]);
	vector<string> errors;
	if (variable1 != nullptr) {
		if (variable2 != nullptr) {
			if (variable1->getTokenType() == IToken::TYPE_TEXT_ARRAY && variable2->getTokenType() == IToken::TYPE_TEXT) {
				if (varArray != nullptr && varArray->variableArrayDictionary.size() > 0) {
					string newDirectory = variable2->getValue();

					newDirectory.erase(remove(newDirectory.begin(), newDirectory.end(), '\"'), newDirectory.end());

					DIR *dir;

					dir = opendir(newDirectory.c_str()); /*your directory*/
					if (dir == nullptr) {
						throwTypeError(*variable2, *variable2, vm);
						return;
					}

					for (auto fileInArray : varArray->variableArrayDictionary) {
						string file = fileInArray->getValue();
						string filename = file;

						const size_t last_slash_idx = filename.find_last_of("\\/");

						if (std::string::npos != last_slash_idx)
						{
							filename.erase(0, last_slash_idx + 1);
						}

						file.erase(remove(file.begin(), file.end(), '\"'), file.end());
						filename.erase(remove(filename.begin(), filename.end(), '\"'), filename.end());

						dir = opendir(file.c_str());
						if (dir != nullptr) {
							throwTypeError(*variable1, *variable1, vm);
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
						bool hasError = false;

						ifstream  src(file, ios::binary);
						if (!src.good()) {
							errors.push_back("Can not open file for copying: " + file);
							hasError = true;
						}
						ifstream  check(newFile, ios::binary);
						if (check.good() && !hasError) {
							errors.push_back("File already exists in this map: " + newFile);
							hasError = true;
						}
						check.close();
						ofstream  dst(newFile, ios::binary);
						if (!dst.good() && !hasError) {
							errors.push_back("Could not write file: " + newFile);
							hasError = true;
						}
						if (!hasError) {
							dst << src.rdbuf();
						}
						src.close();
						dst.close();
					}
					for (auto err : errors) {
						throwCustomError(err, vm);
					}
					return;
			}
				throwCustomError("Array is empty.", vm);
				return;
		}
			throwCustomError("Parameters must be of type text.", vm);
			return;
	}
}
	throwCustomError("Can't find ", vm);
}

pair<string, string> CopyFilesCommand::accept(CommandVisitor & cmdVisitor)
{
	return cmdVisitor.visit(*this);
}