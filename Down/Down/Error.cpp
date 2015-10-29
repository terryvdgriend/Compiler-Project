#include "stdafx.h"
#include "Error.h"


Error::Error(std::string _name, type _type)
{
	name = _name;
	t = _type;
}

Error::Error(std::string _name, std::string _file, int _line, int _column, notice _notice)
{
	name = _name;
	file = _file;
	line = _line;
	column = _column;

	// Voor even zo
	note = "Error";
	if (_notice == warning)
		note = "Warning";
}

void Error::print()
{
	Text::Print("Line: '1' - Column: '2' - ");
	Text::Print("FILE.MD - ");
	Text::Print(name + " - ");
	//Een lijn
	Text::Print("\n");
}

std::string Error::asJsonObject()
{
    std::string JSON = "{";
    JSON += "\"description\":\"" + name + "\", ";
    JSON += "\"line\":\"" + std::to_string(line) + "\", ";
    JSON += "\"column\":\"" + std::to_string(column) + "\", ";
    JSON += "\"file\":\"" + file + "\", ";
    JSON += "\"notice\":\"" + note + "\"";
    //JSON += "\"description\":\"" + name + "\"";
    JSON += "}";
    return JSON;
}

Error::~Error()
{
}
