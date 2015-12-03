#pragma once
#include "VariableType.h"

class Variable
{
	public:
		Variable(string param);
		VariableType getType();
		string getValue();
		void setTokenType(Token::iToken tokentype);
		Token::iToken getTokenType();
	private:
		string value;
		bool is_number(const string& s);
		VariableType type;
		bool is_bool(const string& s);
		Token::iToken tokenType;
};