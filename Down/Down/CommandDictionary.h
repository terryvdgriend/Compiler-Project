#pragma once
#include "BaseCommand.h"
#include "Function.h"

class CommandDictionary
{
	public:
		CommandDictionary();

		map<string, shared_ptr<BaseCommand>>& getMap();
		static list<shared_ptr<Function>>   getCustomFunctions();

	private:
		map<string, shared_ptr<BaseCommand>> commandDictionary;
};