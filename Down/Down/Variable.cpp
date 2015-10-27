#pragma once
#include "stdafx.h"
#include "Variable.h"

using namespace std;

Variable::Variable(string param)
{
	value = param;
	int val;
	bool bol;

	if (is_number(value)) {
		type = VariableType::NUMBER;
	}
	if (is_bool(value)) {
		type = VariableType::BOOL;
	}
	else {
		type = VariableType::TEXT;
	}
}

Variable::~Variable()
{
}

VariableType Variable::getType() {
	return type;
}

string Variable::getValue() {
	return value;
}

bool Variable::is_number(const string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

bool is_bool(const string& s) {
	if (s == "true" || s == "false") {
		return true;
	}
	return false;
}