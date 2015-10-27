#pragma once
#include "stdafx.h"
#include "CommandDictionary.h"
#include "CommandList.h"

CommandDictionary::CommandDictionary()
{
	commandDictionary["$="] = new EqualsCommand();

	commandDictionary["$<"] = new SmallerThanCommand();
	commandDictionary["$<="] = new SmallerEqualsToCommand();
	commandDictionary["$=="] = new EqualsToCommand();
	commandDictionary["$!="] = new NotEqualsToCommand();
	commandDictionary["$>="] = new GreaterEqualsToCommand();
	commandDictionary["$>"] = new GreaterThanCommand();

	commandDictionary["$*"] = new TimesCommand();
	commandDictionary["$/"] = new DivideCommand();
	commandDictionary["$+"] = new PlusCommand();
	commandDictionary["$-"] = new MinusCommand();
	commandDictionary["$++"] = new PlusPlusCommand();
	commandDictionary["$--"] = new MinusMinusCommand();

	commandDictionary["ReturnToVariable"] = new ReturnToVariableCommand();
	commandDictionary["SetIdentifierToReturnValue"] = new IdentifierToReturnValueCommand();
	commandDictionary["SetConstantToReturnValue"] = new ConstantToReturnValueCommand();
	commandDictionary["GetFromReturnValue"] = new GetFromValueCommand();
}

CommandDictionary::~CommandDictionary()
{
	//Todo
}

map<string, BaseCommand*> CommandDictionary::getMap()
{
	return commandDictionary;
}