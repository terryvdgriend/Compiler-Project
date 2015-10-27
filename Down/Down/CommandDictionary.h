#pragma once
#include "BaseCommand.h"

using namespace std;

class CommandDictionary
{
	public:
		CommandDictionary();
		~CommandDictionary();
		map<string, BaseCommand*> getMap();

	private:
		map<string, BaseCommand*> commandDictionary;
};