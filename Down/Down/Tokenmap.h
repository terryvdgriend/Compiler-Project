#pragma once
struct TokenMap{
	static map<string, Token::iToken> get()
	{
		map<string, Token::iToken> mappert;
		//
		mappert[std::string("false")] = Token::BOOL;
		mappert[std::string("true")] = Token::BOOL;
		mappert[std::string("\n")] = Token::NEWLINE;
		mappert[std::string("secret")] = Token::PRIVATE;
		mappert[std::string("#### if")] = Token::IF;
		mappert[std::string("#### switch")] = Token::SWITCH;
		mappert[std::string("#### else")] = Token::ELSE;
		mappert[std::string("#### else if")] = Token::ELIF;
		mappert[std::string("#### for")] = Token::FOR;
		mappert[std::string("#### foreach")] = Token::FOREACH;
		mappert[std::string("#### while")] = Token::WHILE;
		mappert[std::string("#### do")] = Token::DO;
		mappert[std::string(":")] = Token::ASSIGNMENT;
		mappert[std::string("---")] = Token::FUNCTION_OPEN;
		mappert[std::string("___")] = Token::FUNCTION_CLOSE;
		mappert[std::string("[")] = Token::FUNCTION_DECLARE_OPEN;
		mappert[std::string("]")] = Token::FUNCTION_DECLARE_CLOSE;
		mappert[std::string("{")] = Token::ARRAY_OPEN;
		mappert[std::string("}")] = Token::ARRAY_CLOSE;
		mappert[std::string("(")] = Token::CONDITION_OPEN;
		mappert[std::string(")")] = Token::CONDITION_CLOSE;
		mappert[std::string("--")] = Token::BODY_OPEN;
		mappert[std::string("__")] = Token::BODY_CLOSED;
		mappert[std::string("is")] = Token::EQUALS;
		mappert[std::string("like")] = Token::EQUALS_TO;
		mappert[std::string("larger than")] = Token::LARGER_THAN;
		mappert[std::string("smaller than")] = Token::LESS_THAN;
		mappert[std::string("in")] = Token::IN;
		mappert[std::string("plus")] = Token::PLUS;
		mappert[std::string("increased")] = Token::PLUSPLUS;
		mappert[std::string("minus")] = Token::MINUS;
		mappert[std::string("decreased")] = Token::MINUSMINUS;
		mappert[std::string("divide")] = Token::DIVIDE;
		mappert[std::string("multiply")] = Token::TIMES;
		mappert[std::string("multiplied by")] = Token::TIMES;
		mappert[std::string("modulo")] = Token::MODULO;
		mappert[std::string("and gives")] = Token::RETURNVALUE;
		mappert[std::string("gets")] = Token::START_PARAMETERS;
		mappert[std::string("with")] = Token::COMINGPARAMETER;
		mappert[std::string(",")] = Token::AND_PARA;
		mappert[std::string("default")] = Token::SWITCH_DEFAULT;
		mappert[std::string("case")] = Token::SWITCH_CASE;
		mappert[std::string("printdown")] = Token::FUNCTION_CALL;//FUNCTION_CALL / PRINT
		mappert[std::string("printup")] = Token::FUNCTION_CALL;
		//
		mappert[std::string("_fact_")] = Token::TYPE_FACT;
		mappert[std::string("_number_")] = Token::TYPE_NUMBER;
		mappert[std::string("_text_")] = Token::TYPE_TEXT;
		//
		return mappert;
	}
	
	

	
	static const map<string, Token::iToken> tm;

};

const map<string, Token::iToken> TokenMap::tm = TokenMap::get();
