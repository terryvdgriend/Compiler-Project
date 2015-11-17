#include "BaseCommand.h"

class CommandDictionary
{
	public:
		CommandDictionary();
		map<string, shared_ptr<BaseCommand>> getMap();

	private:
		map<string, shared_ptr<BaseCommand>> commandDictionary;
};