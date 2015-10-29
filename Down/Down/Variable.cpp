#include "stdafx.h"
#include "Variable.h"

Variable::Variable(string param) 
	: value{ param }
{
	if (&param == nullptr) 
	{
		type = VariableType::NULLTYPE;
	}
	if (is_number(value)) 
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

bool Variable::is_number(const string& s)
{
	string::const_iterator it = s.begin();

	while (it != s.end() && isdigit(*it))
	{
		++it;
	}

	return !s.empty() && it == s.end();
}

bool Variable::is_bool(const string& s)
{
	if (s == "true" || s == "false") 
	{
		return true;
	}

	return false;
}