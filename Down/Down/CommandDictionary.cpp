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

	commandDictionary["$PRINTDOWN"]						= make_shared<ShowFunctionCommand>();
	commandDictionary["$PRINTUP"]					= make_shared<ShowUpFunctionCommand>();
}

map<string, shared_ptr<BaseCommand>> CommandDictionary::getMap()
{
	return commandDictionary;
}