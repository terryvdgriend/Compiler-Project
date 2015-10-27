#pragma once

#include "VariableType.h"

class Variable
{
	public:
		Variable(string param);
		~Variable();
		VariableType getType();
	private:
		string value;
		bool is_number(const string& s);
		VariableType type;
};