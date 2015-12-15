#include "stdafx.h"
#include "Error.h"


Error::Error(std::string _name, location _location)
{
	name = _name;
	t = _location;
}

Error::Error(std::string _name, std::string _file, int _line, int _column, errorType _errorType)
{
	name = _name;
	file = _file;
	line = _line;
	column = _column;

	// Voor even zo
	errorTypeString = "Error";
	if (_errorType == warning)
		errorTypeString = "Warning";
}


void Error::print()
{
	Text::Print(string(name + "  |  line/col: " + to_string(line) + "/" + to_string(column) + " | type: " + errorTypeString + " \r\n"));

}

std::string Error::asJsonObject()
{
	std::string JSON = "{";
	JSON += "\"description\":\"" + name + "\", ";
	JSON += "\"line\":\"" + std::to_string(line) + "\", ";
	JSON += "\"column\":\"" + std::to_string(column) + "\", ";
	JSON += "\"file\":\"" + file + "\", ";
	JSON += "\"errorType\":\"" + errorTypeString + "\"";
	//JSON += "\"description\":\"" + name + "\"";
	JSON += "}";
	return JSON;
}

Error::~Error()
{
}
