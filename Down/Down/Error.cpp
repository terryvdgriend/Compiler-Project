#include "stdafx.h"
#include "Error.h"
#include "Text.h"

Error::Error(string name, ErrorLocation location)
{
    _name		= name;
    _location	= location;
	_line		= -1;
	_column		= -1;
}

Error::Error(string name, string file, int line, int column, ErrorType errorType)
{
    _name	= name;
    _file	= file;
    _line	= line;
    _column = column;

	_errorTypeString = "Error";

	if (errorType == ErrorType::WARNING)
	{
		_errorTypeString = "Warning";
	}
}

void Error::print()
{
	Text::print(_name + "  |  line/col: " + 
				to_string(_line) + "/" + 
				to_string(_column) + " | type: " +
				_errorTypeString + " \r\n");
}

string Error::asJsonObject()
{
	string JSON = "{";
	JSON += "\"description\":\"" + _name + "\", ";
	JSON += "\"line\":\"" + to_string(_line) + "\", ";
	JSON += "\"column\":\"" + to_string(_column) + "\", ";
	JSON += "\"file\":\"" + _file + "\", ";
	JSON += "\"errorType\":\"" + _errorTypeString + "\"";
	JSON += "}";

	return JSON;
}

string Error::getName()
{
	return _name;
}

void Error::setName(string name)
{
	_name = name;
}

void Error::setLineColumn(int line, int column)
{
	_line	= line;
	_column = column;
}

void Error::setLocation(ErrorLocation location)
{
	_location = location;
};

void Error::setFile(string file)
{
	_file = file;
}