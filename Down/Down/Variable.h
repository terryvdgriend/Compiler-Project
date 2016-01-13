#pragma once
#include "VariableType.h"
class VirtualMachine;

class Variable
{
	public:
		Variable();
		Variable(string param);

		VariableType getType();
		string getValue();
		IToken getTokenType();
		void setTokenType(IToken tokentype, VirtualMachine& vm);

	private:
		string _value;
		IToken _tokenType;
		VariableType _variableType;

		bool is_number(const string& s);
		bool is_bool(const string& s);
};