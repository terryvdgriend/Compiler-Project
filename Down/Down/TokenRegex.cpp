#include "stdafx.h"
#include "TokenRegex.h"

const map<string, IToken> TokenRegex::getTokenRegex()
{
	map<string, IToken> tokenRegex;
	tokenRegex["^-?\\d\.?\\d*$"]		= IToken::NUMBER;
	tokenRegex["^\"(.*?)\"$"]			= IToken::TEXT;
	tokenRegex["^\\*\\*(\\w*)?\\*\\*$"] = IToken::IDENTIFIER;
	tokenRegex["^(__(\\w*)__)$"]		= IToken::DECLARATION;
	tokenRegex["^(### (\\w*)$)"]		= IToken::FUNCTION_DECLARE;
	tokenRegex["^(## (\\w*))$"]			= IToken::CLASS;
	tokenRegex["^(# (\\w*))$"]			= IToken::NAMESPACE;
	tokenRegex["^>.*\n"]				= IToken::COMMENT;

	return tokenRegex;
}