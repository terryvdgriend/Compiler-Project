#pragma once
struct TokenRegex{
	static map<string, Token::iToken> get()
	{
		map<string, Token::iToken> regexert;
		//
		regexert[std::string("\\d")] = Token::NUMBER; //Regex
		regexert[std::string("^\".*?\"$")] = Token::TEXT; // Regex
		regexert[std::string("(true|false)")] = Token::BOOL;
		regexert[std::string("^\\*\\*(\\w*)?\\*\\*$")] = Token::IDENTIFIER; //Regex
		regexert[std::string("^(__(\\w*)__)$")] = Token::DECLARATION; // Regex
		regexert[std::string("^(### (\\w*)$)")] = Token::FUNCTION; //Regex
		regexert[std::string("^(## (\\w*))$")] = Token::CLASS; //Regex
		regexert[std::string("^(# (\\w*))$")] = Token::NAMESPACE; //Regex
		regexert[std::string("^>.*\n")] = Token::COMMENT; //Regex
		regexert[std::string("\n")] = Token::NEWLINE;
		regexert[std::string("secret")] = Token::PRIVATE;
		regexert[std::string("^#### if$")] = Token::IF;
		regexert[std::string("^#### switch$")] = Token::SWITCH;
		regexert[std::string("^#### else$")] = Token::ELSE;
		regexert[std::string("^#### else if$")] = Token::ELIF;
		regexert[std::string("^#### for$")] = Token::FOR;
		regexert[std::string("^#### foreach$")] = Token::FOREACH;
		regexert[std::string("^#### while$")] = Token::WHILE;
		regexert[std::string("^#### do$")] = Token::DO;
		regexert[std::string("^:$")] = Token::ASSIGNMENT;
		regexert[std::string("^---$")] = Token::FUNCTION_OPEN;
		regexert[std::string("^___$")] = Token::FUNCTION_CLOSE;
		regexert[std::string("^\\[$")] = Token::FUNCTION_DECLARE_OPEN;
		regexert[std::string("^\\]$")] = Token::FUNCTION_DECLARE_CLOSE;
		regexert[std::string("^\\{$")] = Token::ARRAY_OPEN;
		regexert[std::string("^\\}$")] = Token::ARRAY_CLOSED;
		regexert[std::string("\\(")] = Token::CONDITION_OPEN;
		regexert[std::string("\\)")] = Token::CONDITION_CLOSE;
		regexert[std::string("^--$")] = Token::BODY_OPEN;
		regexert[std::string("^__$")] = Token::BODY_CLOSED;
		regexert[std::string("is")] = Token::EQUALS;
		regexert[std::string("like")] = Token::EQUALS_TO;
		regexert[std::string("larger than")] = Token::LARGER_THAN;
		regexert[std::string("smaller than")] = Token::LESS_THAN;
		regexert[std::string("in")] = Token::IN;
		regexert[std::string("plus")] = Token::PLUS;
		regexert[std::string("increased")] = Token::PLUSPLUS;
		regexert[std::string("minus")] = Token::MINUS;
		regexert[std::string("decreased")] = Token::MINUSMINUS;
		regexert[std::string("divide")] = Token::DIVIDE;
		regexert[std::string("^multiplied by|multiply$")] = Token::TIMES;
		regexert[std::string("modulo")] = Token::MODULO;
		regexert[std::string("^and gives$")] = Token::RETURNVALUE;
		regexert[std::string("^gets$")] = Token::START_PARAMETERS;
		regexert[std::string("^with$")] = Token::COMINGPARAMETER;
		regexert[std::string("^,")] = Token::AND_PARA;
		regexert[std::string("^default$")] = Token::SWITCH_DEFAULT;
		regexert[std::string("^case$")] = Token::SWITCH_CASE;
		//
		return regexert;
	}
	static const map<string, Token::iToken> tr;
};
const map<string, Token::iToken> TokenRegex::tr = TokenRegex::get();