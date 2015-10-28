#pragma once

#include "VariableType.h"

class Variable
{
	public:
		Variable(string param);
		~Variable();
		VariableType getType();
		string getValue();
	private:
		string value;
		bool is_number(const string& s);
		VariableType type;
};