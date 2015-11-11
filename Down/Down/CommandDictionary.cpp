#include "stdafx.h"
#include "CommandDictionary.h"
#include "CommandList.h"

CommandDictionary::CommandDictionary()
{
	commandDictionary["$="]							= shared_ptr<BaseCommand>(new EqualsCommand());

	commandDictionary["$<"]							= shared_ptr<BaseCommand>(new SmallerThanCommand());
	commandDictionary["$<="]						= shared_ptr<BaseCommand>(new SmallerEqualsToCommand());
	commandDictionary["$=="]						= shared_ptr<BaseCommand>(new EqualsToCommand());
	commandDictionary["$!="]						= shared_ptr<BaseCommand>(new NotEqualsToCommand());
	commandDictionary["$>="]						= shared_ptr<BaseCommand>(new GreaterEqualsToCommand());
	commandDictionary["$>"]							= shared_ptr<BaseCommand>(new GreaterThanCommand());

	commandDictionary["$*"]							= shared_ptr<BaseCommand>(new TimesCommand());
	commandDictionary["$/"]							= shared_ptr<BaseCommand>(new DivideCommand());
	commandDictionary["$%"]							= shared_ptr<BaseCommand>(new ModuloCommand());
	commandDictionary["$+"]							= shared_ptr<BaseCommand>(new PlusCommand());
	commandDictionary["$-"]							= shared_ptr<BaseCommand>(new MinusCommand());
	commandDictionary["$++"]						= shared_ptr<BaseCommand>(new PlusPlusCommand());
	commandDictionary["$--"]						= shared_ptr<BaseCommand>(new MinusMinusCommand());

	commandDictionary["IdentifierToReturnValue"]	= shared_ptr<BaseCommand>(new IdentifierToReturnValueCommand());
	commandDictionary["ConstantToReturnValue"]		= shared_ptr<BaseCommand>(new ConstantToReturnValueCommand());
	commandDictionary["getFromReturnValue"]			= shared_ptr<BaseCommand>(new GetFromValueCommand());

	commandDictionary["$FUNC"]						= shared_ptr<BaseCommand>(new ShowFunctionCommand());
}

map<string, shared_ptr<BaseCommand>> CommandDictionary::getMap()
{
	return commandDictionary;
}