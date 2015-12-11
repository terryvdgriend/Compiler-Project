#include "stdafx.h"
#include "TokenRegex.h"

const map<string, IToken> TokenRegex::getTokenRegex()
{
	map<string, IToken> tokenRegex;
	tokenRegex["^(## (\\w*))$"]				= IToken::CLASS;
	tokenRegex["^>.*\n"]					= IToken::COMMENT;
	tokenRegex["^(__(\\w*)__)$"]			= IToken::DECLARATION;
	tokenRegex["^(### (\\w*)$)"]			= IToken::FUNCTION_DECLARE;
	tokenRegex["^\\*\\*(\\w*)?\\*\\*$"]		= IToken::IDENTIFIER;
	tokenRegex["^(# (\\w*))$"]				= IToken::NAMESPACE;
	tokenRegex["^-?\\d\.?\\d*$"]			= IToken::NUMBER;
	tokenRegex["^\"(.*?)\"$"]				= IToken::TEXT;

	return tokenRegex;
}