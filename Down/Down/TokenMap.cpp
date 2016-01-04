#include "stdafx.h"
#include "TokenMap.h"

const map<string, IToken> TokenMap::getTokenMap()
{
	map<string, IToken> tokenMap;

	// Accessibility Tokens
	tokenMap["secret"]					= IToken::PRIVATE;

	// Array Tokens
	tokenMap["}"]						= IToken::ARRAY_CLOSE;
	tokenMap["{"]						= IToken::ARRAY_OPEN;
	tokenMap["in"]						= IToken::IN;

	// Conditional Tokens
	tokenMap["#### else"]				= IToken::ELSE;
	tokenMap["#### else if"]			= IToken::ELSEIF;
	tokenMap["#### if"]					= IToken::IF;
	tokenMap["#### switch"]				= IToken::SWITCH;
	tokenMap["case"]					= IToken::SWITCH_CASE;
	tokenMap["default"]					= IToken::SWITCH_DEFAULT;

	// Function Tokens
	tokenMap["___"]						= IToken::FUNCTION_CLOSE;
	tokenMap["---"]						= IToken::FUNCTION_OPEN;
	tokenMap["]"]						= IToken::FUNCTION_DECLARE_CLOSE;
	tokenMap["["]						= IToken::FUNCTION_DECLARE_OPEN;

	// Loop Tokens
	tokenMap["#### do"]					= IToken::DO;
	tokenMap["#### for"]				= IToken::FOR;
	tokenMap["#### foreach"]			= IToken::FOREACH;
	tokenMap["#### while"]				= IToken::WHILE;

	// Miscellaneous Tokens
	tokenMap[","]						= IToken::AND_PARA;
	tokenMap[":"]						= IToken::ASSIGNMENT;
	tokenMap["__"]						= IToken::BODY_CLOSE;
	tokenMap["--"]						= IToken::BODY_OPEN;
	tokenMap["with"]					= IToken::COMINGPARAMETER;
	tokenMap[")"]						= IToken::CONDITION_CLOSE;
	tokenMap["("]						= IToken::CONDITION_OPEN;
	tokenMap["false"]					= IToken::FACT;
	tokenMap["true"]					= IToken::FACT;
	tokenMap["\n"]						= IToken::NEWLINE;
	tokenMap["and gives"]				= IToken::RETURNVALUE;
	tokenMap["gives"]				= IToken::RETURNVALUE;
	tokenMap["gets"]					= IToken::START_PARAMETERS;
	
	// Operators Tokens
	tokenMap["divide"]					= IToken::DIVIDE;
	tokenMap["is"]						= IToken::EQUALS;
	tokenMap["like"]					= IToken::EQUALS_TO;
	tokenMap["like or larger than"]		= IToken::LARGER_LIKE_THAN;
	tokenMap["larger than"]				= IToken::LARGER_THAN;
	tokenMap["like or smaller than"]	= IToken::LESS_LIKE_THAN;
	tokenMap["smaller than"]			= IToken::LESS_THAN;
	tokenMap["minus"]					= IToken::MINUS;
	tokenMap["decreased"]				= IToken::MINUSMINUS;
	tokenMap["modulo"]					= IToken::MODULO;
	tokenMap["plus"]					= IToken::PLUS;
	tokenMap["increased"]				= IToken::PLUSPLUS;
	tokenMap["multiplied by"]			= IToken::TIMES;
	tokenMap["multiply"]				= IToken::TIMES;

	// Types Tokens
	tokenMap["_fact_"]					= IToken::TYPE_FACT;
	tokenMap["_number_"]				= IToken::TYPE_NUMBER;
	tokenMap["_text_"]					= IToken::TYPE_TEXT;

	for (pair<string, shared_ptr<BaseCommand>> cf : CommandDictionary::getCustomFunctions())
	{
		tokenMap[cf.first] = IToken::FUNCTION_CALL;
	}

	return tokenMap;
}