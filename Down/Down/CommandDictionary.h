#include "BaseCommand.h"

using namespace std;

class CommandDictionary
{
	public:
		CommandDictionary();
		map<string, BaseCommand*> getMap();

	private:
		map<string, BaseCommand*> commandDictionary;
};