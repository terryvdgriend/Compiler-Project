#pragma once
#include "stdafx.h"
#include "CommandDictionary.h"
#include "EqualsCommand.h"

CommandDictionary::CommandDictionary()
{
	commandDictionary["$="] = new EqualsCommand();
}

CommandDictionary::~CommandDictionary()
{
	// Todo cleanup
}

map<string, BaseCommand*> CommandDictionary::getMap()
{
	return commandDictionary;
}