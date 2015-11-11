#include "BaseCommand.h"

using namespace std;

class CommandDictionary
{
	public:
		CommandDictionary();
		map<string, shared_ptr<BaseCommand>> getMap();

	private:
		map<string, shared_ptr<BaseCommand>> commandDictionary;
};