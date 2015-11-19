#pragma once
#include "VariableType.h"

class Variable
{
	public:
		Variable() {}
		Variable(string param);
		VariableType getType();
		string getValue();
	private:
		string value;
		bool is_number(const string& s);
		VariableType type;
		bool is_bool(const string& s);
};