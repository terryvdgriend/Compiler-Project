#include "stdafx.h"
#include "Variable.h"

Variable::Variable(string param) 
{
	value = param;
	if (&param == nullptr || param == "") 
	{
		type = VariableType::NULLTYPE;
	}
	else if (is_number(value)) 
	{
		type = VariableType::NUMBER;
	}
	else if (is_bool(value)) 
	{
		type = VariableType::BOOL;
	}
	else 
	{
		type = VariableType::TEXT;
	}
	
}

VariableType Variable::getType() 
{
	return type;
}

string Variable::getValue() 
{
	return value;
}

void Variable::setTokenType(Token::iToken tokentype)
{
	this->tokenType = tokentype;
}

Token::iToken Variable::getTokenType()
{
	return this->tokenType;
}

bool Variable::is_number(const string& s)
{
	string::const_iterator it = s.begin();
	bool decimalPoint = false;
	int minSize = 0;
	if (s.size()>0 && (s[0] == '-' || s[0] == '+')) {
		it++;
		minSize++;
	}
	while (it != s.end()) {
		if (*it == '.') {
			if (!decimalPoint) decimalPoint = true;
			else break;
		}
		else if (!isdigit(*it) && ((*it != 'f') || it + 1 != s.end() || !decimalPoint)) {
			break;
		}
		++it;
	}
	return s.size()>minSize && it == s.end();
}

bool Variable::is_bool(const string& s)
{
	if (s == "true" || s == "false") 
	{
		return true;
	}

	return false;
}