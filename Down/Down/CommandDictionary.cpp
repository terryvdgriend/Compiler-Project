#pragma once
#include "stdafx.h"
#include "CommandDictionary.h"
#include "CommandList.h"

 map<string, shared_ptr<BaseCommand>>  CommandDictionary::CustFunc()
{
	map<string, shared_ptr<BaseCommand>> asd;
	asd["printdown"] = std::make_shared<ShowFunctionCommand>();
	asd["printup"] = std::make_shared<ShowUpFunctionCommand>();
	asd["random"] = std::make_shared<RandomFunctionCommand>();
	asd["ThrowError"] = std::make_shared<ErrorCommand>();

	// LEES: 
	// als je een eigen functie wil toevoegen, geef dan de naam op van de functie (zoals wij hem in code gaan typen)
	// en geef dan aan welke classe hiervoor gebruikt moet worden (die overigens wel een baseCommand override)
	
	//asd["DOEIETS"] = std::make_shared<ShowFunctionCommand>();
	
	//
	return asd;
};

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

	commandDictionary["$AddArrayToDictionary"]		= make_shared<AddArrayToDictionaryCommand>();
	commandDictionary["$AddLengthToArray"]			= make_shared<AddLengthToArrayCommand>();
	commandDictionary["$AddItemToArrayAt"]			= make_shared<AddItemToArrayAtCommand>();
	commandDictionary["$GetItemFromArray"]			= make_shared<GetItemFromArrayCommand>();

	commandDictionary["IdentifierToReturnValue"]	= make_shared<IdentifierToReturnValueCommand>();
	commandDictionary["ConstantToReturnValue"]		= make_shared<ConstantToReturnValueCommand>();
	commandDictionary["getFromReturnValue"]			= make_shared<GetFromValueCommand>();

	for (std::pair<string, shared_ptr<BaseCommand>> cf : CustFunc())
	{
		commandDictionary[std::string(cf.first)] = cf.second;
	}
}

map<string, shared_ptr<BaseCommand>> CommandDictionary::getMap()
{
	return commandDictionary;
}