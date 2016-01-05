#include "stdafx.h"
#include "CommandDictionary.h"
#include "MandatoryCommandVisitorIncludes.h"


CommandDictionary::CommandDictionary()
{
	// Array
	commandDictionary["$AddArrayToDictionary"]		= make_shared<AddArrayToDictionaryCommand>();
	commandDictionary["$AddItemToArrayAt"]			= make_shared<AddItemToArrayAtCommand>();
	commandDictionary["$AddLengthToArray"]			= make_shared<AddLengthToArrayCommand>();
	commandDictionary["$GetItemFromArray"]			= make_shared<GetItemFromArrayCommand>();

	// Miscellaneous
	commandDictionary["ConstantToReturnValue"]		= make_shared<ConstantToReturnValueCommand>();
	commandDictionary["getFromReturnValue"]			= make_shared<GetFromValueCommand>();
	commandDictionary["IdentifierToReturnValue"]	= make_shared<IdentifierToReturnValueCommand>();
	
	// Operators
	commandDictionary["$/"]							= make_shared<DivideCommand>();
	commandDictionary["$="]							= make_shared<EqualsCommand>();
	commandDictionary["$=="]						= make_shared<EqualsToCommand>();
	commandDictionary["$>="]						= make_shared<GreaterEqualsToCommand>();
	commandDictionary["$>"]							= make_shared<GreaterThanCommand>();
	commandDictionary["$-"]							= make_shared<MinusCommand>();
	commandDictionary["$--"]						= make_shared<MinusMinusCommand>();
	commandDictionary["$%"]							= make_shared<ModuloCommand>();
	commandDictionary["$!="]						= make_shared<NotEqualsToCommand>();
	commandDictionary["$+"]							= make_shared<PlusCommand>();
	commandDictionary["$++"]						= make_shared<PlusPlusCommand>();
	commandDictionary["$<="]						= make_shared<SmallerEqualsToCommand>();
	commandDictionary["$<"]							= make_shared<SmallerThanCommand>();
	commandDictionary["$*"]							= make_shared<TimesCommand>();

	for (auto ff : getCustomFunctions())
	{
		commandDictionary[ff->getName()] =ff->getCommand();
	}
}

map<string, shared_ptr<BaseCommand>>& CommandDictionary::getMap()
{
	return commandDictionary;
}

list<shared_ptr<Function>>  CommandDictionary::getCustomFunctions()
{
	//map<string, shared_ptr<BaseCommand>> customFunctionDictionary;
	//customFunctionDictionary["printdown"] = make_shared<ShowFunctionCommand>();

	list<shared_ptr<Function>> customFunctionDictionary;
	auto vecToken = vector<shared_ptr<Token>>();

	customFunctionDictionary.push_back(make_shared<Function>("printdown", "aa", make_shared<ShowFunctionCommand>(), vecToken));
	customFunctionDictionary.push_back(make_shared<Function>("printdown", "a", make_shared<ShowFunctionCommand>(), vecToken));

	customFunctionDictionary.push_back(make_shared<Function>("printup", "a", make_shared<ShowUpFunctionCommand>(), vecToken));
	customFunctionDictionary.push_back(make_shared<Function>("random", "a", make_shared<RandomFunctionCommand>(), vecToken));
	customFunctionDictionary.push_back(make_shared<Function>("ThrowError", "a", make_shared<ErrorCommand>(), vecToken));
	customFunctionDictionary.push_back(make_shared<Function>("getAllFilesInDirectory", "a", make_shared<GetAllFilesInDirectoryCommand>(), vecToken));
	customFunctionDictionary.push_back(make_shared<Function>("getVideoFilesInDirectory", "a", make_shared<GetVideoFilesInDirectoryCommand>(), vecToken));
	customFunctionDictionary.push_back(make_shared<Function>("getAudioFilesInDirectory", "a", make_shared<GetAudioFilesInDirectoryCommand>(), vecToken));
	customFunctionDictionary.push_back(make_shared<Function>("count", "a", make_shared<CountCommand>(), vecToken));
	customFunctionDictionary.push_back(make_shared<Function>("getFileExtension", "a", make_shared<GetFileExtensionCommand>(), vecToken));
	

	/*
		READ:
		If you want to define your own function(s), provide a name for the function and 
		couple a BaseCommand implementation as shown in the above function declerations.
	*/

	return customFunctionDictionary;
};