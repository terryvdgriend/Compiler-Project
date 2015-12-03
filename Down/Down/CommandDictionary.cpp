#include "stdafx.h"
#include "CommandDictionary.h"
#include "CommandList.h"

CommandDictionary::CommandDictionary()
{
	commandDictionary["$="]							= make_shared<EqualsCommand>();

	commandDictionary["$<"]							= make_shared<SmallerThanCommand>();
	commandDictionary["$<="]						= make_shared<SmallerEqualsToCommand>();
	commandDictionary["$=="]						= make_shared<EqualsToCommand>();
	commandDictionary["$!="]						= make_shared<NotEqualsToCommand>();
	commandDictionary["$>="]						= make_shared<GreaterEqualsToCommand>();
	commandDictionary["$>"]							= make_shared<GreaterThanCommand>();

	commandDictionary["$*"]							= make_shared<TimesCommand>();
	commandDictionary["$/"]							= make_shared<DivideCommand>();
	commandDictionary["$%"]							= make_shared<ModuloCommand>();
	commandDictionary["$+"]							= make_shared<PlusCommand>();
	commandDictionary["$-"]							= make_shared<MinusCommand>();
	commandDictionary["$++"]						= make_shared<PlusPlusCommand>();
	commandDictionary["$--"]						= make_shared<MinusMinusCommand>();

	commandDictionary["IdentifierToReturnValue"]	= make_shared<IdentifierToReturnValueCommand>();
	commandDictionary["ConstantToReturnValue"]		= make_shared<ConstantToReturnValueCommand>();
	commandDictionary["getFromReturnValue"]			= make_shared<GetFromValueCommand>();
	
	for (pair<string, shared_ptr<BaseCommand>> cf : getCustomFunctions())
	{
		commandDictionary[cf.first] = cf.second;
	}
}

map<string, shared_ptr<BaseCommand>>& CommandDictionary::getMap()
{
	return commandDictionary;
}

map<string, shared_ptr<BaseCommand>>  CommandDictionary::getCustomFunctions()
{
	map<string, shared_ptr<BaseCommand>> customFunctionDictionary;
	customFunctionDictionary["printdown"]			= make_shared<ShowFunctionCommand>();
	customFunctionDictionary["printup"]				= make_shared<ShowUpFunctionCommand>();
	customFunctionDictionary["random"]				= make_shared<RandomFunctionCommand>();
	customFunctionDictionary["ditwerkt"]			= make_shared<RandomFunctionCommand>();

	/*
		READ:
		If you want to define your own function(s), provide a name for the function and 
		couple a BaseCommand implementation as shown in the above function declerations.
	*/

	return customFunctionDictionary;
};