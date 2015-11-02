#pragma once

class Error
{
public:
	enum location { tokenizer, compiler, vm };
	enum errorType { warning, error };
private:
	std::string name;
	int line{ -1 };
	int column{ -1 };
	location t;
	std::string errorTypeString;
	std::string file;
public:
	Error(std::string _name, location _location);
	Error(std::string _name, std::string _file, int _line, int _column, errorType _type);
	void print();
	std::string asJsonObject();

	// GET;SET;
	void setName(std::string n){ name = n; };
	void setLineColumn(int l, int c){ line = l; column = c; };
	void setType(location tt){ t = tt; };
	void setFile(std::string f){ file = f; };
	//
	~Error();
};

