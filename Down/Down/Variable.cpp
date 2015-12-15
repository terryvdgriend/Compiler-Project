#include "stdafx.h"
#include "Variable.h"

Variable::Variable()
{
	// 
}

Variable::Variable(string param) 
{
	_value = param;

	if (&param == nullptr || param == "") 
	{
		_variableType = VariableType::nulltype;
	}
	else if (is_number(_value)) 
	{
		_variableType = VariableType::number;
	}
	else if (is_bool(_value)) 
	{
		_variableType = VariableType::fact;
	}
	else 
	{
		_variableType = VariableType::text;
	}	
}

VariableType Variable::getType() 
{
	return _variableType;
}

string Variable::getValue() 
{
	return _value;
}

IToken Variable::getTokenType()
{
	return _tokenType;
}

void Variable::setTokenType(IToken tokentype)
{
	_tokenType = tokentype;
}

bool Variable::is_number(const string& s)
{
	string::const_iterator it = s.begin();
	bool decimalPoint = false;
	int minSize = 0;

	if (s.size()>0 && (s[0] == '-' || s[0] == '+')) 
	{
		it++;
		minSize++;
	}

	while (it != s.end())
	{
		if (*it == '.') 
		{
			if (!decimalPoint)
			{
				decimalPoint = true;
			}
			else
			{
				break;
			}
		}
		else if (!isdigit(*it) && ((*it != 'f') || it + 1 != s.end() || !decimalPoint)) 
		{
			break;
		}
		++it;
	}

	return s.size() > (size_t)minSize && it == s.end();
}

bool Variable::is_bool(const string& s)
{
	if (s == "true" || s == "false") 
	{
		return true;
	}

	return false;
}