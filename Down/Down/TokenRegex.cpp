#include "stdafx.h"
#include "TokenRegex.h"

const map<string, IToken> TokenRegex::getTokenRegex()
{
	map<string, IToken> tokenRegex;
	tokenRegex[string("^-?\\d\.?\\d*$")]		= IToken::NUMBER;
	tokenRegex[string("^\"(.*?)\"$")]			= IToken::TEXT;
	tokenRegex[string("^\\*\\*(\\w*)?\\*\\*$")] = IToken::IDENTIFIER;
	tokenRegex[string("^(__(\\w*)__)$")]		= IToken::DECLARATION;
	tokenRegex[string("^(### (\\w*)$)")]		= IToken::FUNCTION_DECLARE;
	tokenRegex[string("^(## (\\w*))$")]			= IToken::CLASS;
	tokenRegex[string("^(# (\\w*))$")]			= IToken::NAMESPACE;
	tokenRegex[string("^>.*\n")]				= IToken::COMMENT;

	return tokenRegex;
}