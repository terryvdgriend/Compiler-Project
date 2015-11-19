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
	commandDictionary["$%"] = new ModuloCommand();
	commandDictionary["$+"] = new PlusCommand();
	commandDictionary["$-"] = new MinusCommand();
	commandDictionary["$++"] = new PlusPlusCommand();
	commandDictionary["$--"] = new MinusMinusCommand();
	commandDictionary["$FUNC"] = new ShowFunctionCommand();

	commandDictionary["$AddArrayToDictionary"] = new AddArrayToDictionary();
	commandDictionary["$AddLengthToArray"] = new AddLengthToArrayCommand();
	commandDictionary["$AddItemToArray"] = new AddItemToArrayCommand();
	commandDictionary["$GetItemFromArray"] = new GetItemFromArrayCommand();

	commandDictionary["IdentifierToReturnValue"] = new IdentifierToReturnValueCommand();
	commandDictionary["ConstantToReturnValue"] = new ConstantToReturnValueCommand();
	commandDictionary["getFromReturnValue"] = new GetFromValueCommand();
}

map<string, BaseCommand*> CommandDictionary::getMap()
{
	return commandDictionary;
}