#include "stdafx.h"
#include "TokenMap.h"

const map<string, IToken> TokenMap::getTokenMap()
{
	map<string, IToken> tokenMap;
	tokenMap[string("false")]			= IToken::BOOL;
	tokenMap[string("true")]			= IToken::BOOL;
	tokenMap[string("\n")]				= IToken::NEWLINE;
	tokenMap[string("secret")]			= IToken::PRIVATE;
	tokenMap[string("#### if")]			= IToken::IF;
	tokenMap[string("#### switch")]		= IToken::SWITCH;
	tokenMap[string("#### else")]		= IToken::ELSE;
	tokenMap[string("#### else if")]	= IToken::ELIF;
	tokenMap[string("#### for")]		= IToken::FOR;
	tokenMap[string("#### foreach")]	= IToken::FOREACH;
	tokenMap[string("#### while")]		= IToken::WHILE;
	tokenMap[string("#### do")]			= IToken::DO;
	tokenMap[string(":")]				= IToken::ASSIGNMENT;
	tokenMap[string("---")]				= IToken::FUNCTION_OPEN;
	tokenMap[string("___")]				= IToken::FUNCTION_CLOSE;
	tokenMap[string("[")]				= IToken::FUNCTION_DECLARE_OPEN;
	tokenMap[string("]")]				= IToken::FUNCTION_DECLARE_CLOSE;
	tokenMap[string("{")]				= IToken::ARRAY_OPEN;
	tokenMap[string("}")]				= IToken::ARRAY_CLOSE;
	tokenMap[string("(")]				= IToken::CONDITION_OPEN;
	tokenMap[string(")")]				= IToken::CONDITION_CLOSE;
	tokenMap[string("--")]				= IToken::BODY_OPEN;
	tokenMap[string("__")]				= IToken::BODY_CLOSED;
	tokenMap[string("is")]				= IToken::EQUALS;
	tokenMap[string("like")]			= IToken::EQUALS_TO;
	tokenMap[string("larger than")]		= IToken::LARGER_THAN;
	tokenMap[string("smaller than")]	= IToken::LESS_THAN;
	tokenMap[string("in")]				= IToken::IN;
	tokenMap[string("plus")]			= IToken::PLUS;
	tokenMap[string("increased")]		= IToken::PLUSPLUS;
	tokenMap[string("minus")]			= IToken::MINUS;
	tokenMap[string("decreased")]		= IToken::MINUSMINUS;
	tokenMap[string("divide")]			= IToken::DIVIDE;
	tokenMap[string("multiply")]		= IToken::TIMES;
	tokenMap[string("multiplied by")]	= IToken::TIMES;
	tokenMap[string("modulo")]			= IToken::MODULO;
	tokenMap[string("and gives")]		= IToken::RETURNVALUE;
	tokenMap[string("gets")]			= IToken::START_PARAMETERS;
	tokenMap[string("with")]			= IToken::COMINGPARAMETER;
	tokenMap[string(",")]				= IToken::AND_PARA;
	tokenMap[string("default")]			= IToken::SWITCH_DEFAULT;
	tokenMap[string("case")]			= IToken::SWITCH_CASE;

	tokenMap[string("_fact_")]			= IToken::TYPE_FACT;
	tokenMap[string("_number_")]		= IToken::TYPE_NUMBER;
	tokenMap[string("_text_")]			= IToken::TYPE_TEXT;

	for (pair<string, shared_ptr<BaseCommand>> cf : CommandDictionary::getCustomFunctions())
	{
		tokenMap[string(cf.first)] = IToken::FUNCTION_CALL;
	}

	return tokenMap;
}