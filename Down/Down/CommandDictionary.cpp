#pragma once
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

map<string, shared_ptr<BaseCommand>> CommandDictionary::getMap()
{
	return commandDictionary;
}

map<string, shared_ptr<BaseCommand>>  CommandDictionary::getCustomFunctions()
{
	map<string, shared_ptr<BaseCommand>> customFunctionDictionary;
	customFunctionDictionary["printdown"]			= make_shared<ShowFunctionCommand>();
	customFunctionDictionary["printup"]				= make_shared<ShowUpFunctionCommand>();
	customFunctionDictionary["random"]				= make_shared<RandomFunctionCommand>();

	// LEES: 
	// als je een eigen functie wil toevoegen, geef dan de naam op van de functie (zoals wij hem in code gaan typen)
	// en geef dan aan welke classe hiervoor gebruikt moet worden (die overigens wel een baseCommand override)

	return customFunctionDictionary;
};