#pragma once
#include "BaseCommand.h"



class CommandDictionary
{

	public:
		CommandDictionary();
		map<string, shared_ptr<BaseCommand>> getMap();
		static map<string, shared_ptr<BaseCommand>> CustFunc();
	private:
		map<string, shared_ptr<BaseCommand>> commandDictionary;
};

