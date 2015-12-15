#pragma once
struct TokenRegex{
	static map<string, Token::iToken> get()
	{
		map<string, Token::iToken> regexert;
		//
		regexert[std::string("^-?\\d\.?\\d*$")] = Token::NUMBER; //Regex
		regexert[std::string("^\"(.*?)\"$")] = Token::TEXT; // Regex
		regexert[std::string("^\\*\\*(\\w*)?\\*\\*$")] = Token::IDENTIFIER; //Regex
		//regexert[std::string("^\\*\\*(\\w*)?\\*\\*(?=(.+ {))")] = Token::ARRAYIDENTIFIER; //Regex // NASTY REGEX
		regexert[std::string("^(__(\\w*)__)$")] = Token::DECLARATION; // Regex
		regexert[std::string("^(### (\\w*)$)")] = Token::FUNCTION_DECLARE; //Regex
		regexert[std::string("^(## (\\w*))$")] = Token::CLASS; //Regex
		regexert[std::string("^(# (\\w*))$")] = Token::NAMESPACE; //Regex
		regexert[std::string(">.*")] = Token::COMMENT; //V0: ^>.*\n   - V1: >.*
		//
		return regexert;
	}
	static const map<string, Token::iToken> tr;
};
const map<string, Token::iToken> TokenRegex::tr = TokenRegex::get();