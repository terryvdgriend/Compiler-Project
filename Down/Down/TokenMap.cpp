#include "stdafx.h"
#include "TokenMap.h"

const map<string, IToken> TokenMap::getTokenMap()
{
	map<string, IToken> tokenMap;
	tokenMap["false"]			= IToken::BOOL;
	tokenMap["true"]			= IToken::BOOL;
	tokenMap["\n"]				= IToken::NEWLINE;
	tokenMap["secret"]			= IToken::PRIVATE;
	tokenMap["#### if"]			= IToken::IF;
	tokenMap["#### switch"]		= IToken::SWITCH;
	tokenMap["#### else"]		= IToken::ELSE;
	tokenMap["#### else if"]	= IToken::ELIF;
	tokenMap["#### for"]		= IToken::FOR;
	tokenMap["#### foreach"]	= IToken::FOREACH;
	tokenMap["#### while"]		= IToken::WHILE;
	tokenMap["#### do"]			= IToken::DO;
	tokenMap[":"]				= IToken::ASSIGNMENT;
	tokenMap["---"]				= IToken::FUNCTION_OPEN;
	tokenMap["___"]				= IToken::FUNCTION_CLOSE;
	tokenMap["["]				= IToken::FUNCTION_DECLARE_OPEN;
	tokenMap["]"]				= IToken::FUNCTION_DECLARE_CLOSE;
	tokenMap["{"]				= IToken::ARRAY_OPEN;
	tokenMap["}"]				= IToken::ARRAY_CLOSE;
	tokenMap["("]				= IToken::CONDITION_OPEN;
	tokenMap[")"]				= IToken::CONDITION_CLOSE;
	tokenMap["--"]				= IToken::BODY_OPEN;
	tokenMap["__"]				= IToken::BODY_CLOSED;
	tokenMap["is"]				= IToken::EQUALS;
	tokenMap["like"]			= IToken::EQUALS_TO;
	tokenMap["larger than"]		= IToken::LARGER_THAN;
	tokenMap["smaller than"]	= IToken::LESS_THAN;
	tokenMap["in"]				= IToken::IN;
	tokenMap["plus"]			= IToken::PLUS;
	tokenMap["increased"]		= IToken::PLUSPLUS;
	tokenMap["minus"]			= IToken::MINUS;
	tokenMap["decreased"]		= IToken::MINUSMINUS;
	tokenMap["divide"]			= IToken::DIVIDE;
	tokenMap["multiply"]		= IToken::TIMES;
	tokenMap["multiplied by"]	= IToken::TIMES;
	tokenMap["modulo"]			= IToken::MODULO;
	tokenMap["and gives"]		= IToken::RETURNVALUE;
	tokenMap["gets"]			= IToken::START_PARAMETERS;
	tokenMap["with"]			= IToken::COMINGPARAMETER;
	tokenMap[","]				= IToken::AND_PARA;
	tokenMap["default"]			= IToken::SWITCH_DEFAULT;
	tokenMap["case"]			= IToken::SWITCH_CASE;

	tokenMap["_fact_"]			= IToken::TYPE_FACT;
	tokenMap["_number_"]		= IToken::TYPE_NUMBER;
	tokenMap["_text_"]			= IToken::TYPE_TEXT;

	for (pair<string, shared_ptr<BaseCommand>> cf : CommandDictionary::getCustomFunctions())
	{
		tokenMap[cf.first] = IToken::FUNCTION_CALL;
	}

	return tokenMap;
}