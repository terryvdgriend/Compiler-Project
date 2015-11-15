#pragma once
struct TokenRegex{
	static map<string, Token::iToken> get()
	{
		map<string, Token::iToken> regexert;
		//
		regexert[std::string("^-?\\d\.?\\d*$")] = Token::NUMBER; //Regex
		regexert[std::string("^\".*?\"$")] = Token::TEXT; // Regex
		regexert[std::string("^\\*\\*(\\w*)?\\*\\*$")] = Token::IDENTIFIER; //Regex
		regexert[std::string("^(__(\\w*)__)$")] = Token::DECLARATION; // Regex
		regexert[std::string("^(### (\\w*)$)")] = Token::FUNCTION; //Regex
		regexert[std::string("^(## (\\w*))$")] = Token::CLASS; //Regex
		regexert[std::string("^(# (\\w*))$")] = Token::NAMESPACE; //Regex
		regexert[std::string("^>.*\n")] = Token::COMMENT; //Regex
		//
		return regexert;
	}
	static const map<string, Token::iToken> tr;
};
const map<string, Token::iToken> TokenRegex::tr = TokenRegex::get();