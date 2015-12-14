#pragma once
#include "ErrorLocation.h"
#include "ErrorType.h"

class Error
{
	public:
		Error(string name, ErrorLocation location);
		Error(string name, string file, int line, int column, ErrorType type);

		void print();
		string asJsonObject();

		string getName();
		void setName(string name); 
		void setLineColumn(int line, int column);
		void setLocation(ErrorLocation location);
		void setFile(string file);

	private:
		string _name;
		int _line;
		int _column;
		ErrorLocation _location;
		string _errorTypeString;
		string _file;
};