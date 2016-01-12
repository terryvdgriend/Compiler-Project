#pragma once
#include "BaseCommand.h"
class GetAudioFilesInDirectoryCommand :
	public BaseCommand
{
public:
	GetAudioFilesInDirectoryCommand();
	~GetAudioFilesInDirectoryCommand();

	// Inherited via BaseCommand
	virtual void execute(VirtualMachine & vm, AbstractFunctionCall & node) override;
	virtual pair<string, string> accept(CommandVisitor & cmdVisitor) override;
private:
	string getExtension(const string fileName);
};

