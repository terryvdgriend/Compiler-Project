#pragma once

class Error
{
public:
	enum type { tokenizer, compiler, vm };
	enum notice { warning, errort };
private:
	std::string name{"Unknown"};
	int line{ -1 };
	int column{ -1 };
	type t;
	std::string note;
	std::string file{"Unknown.MD"};
public:
	Error(std::string _name, type _type);
	Error(std::string _name, std::string _file, int _line, int _column, notice _notice);
	void print();
	std::string asJsonObject();

	// GET;SET;
	void setName(std::string n){ name = n; };
	void setLineColumn(int l, int c){ line = l; column = c; };
	void setType(type tt){ t = tt; };
	void setFile(std::string f){ file = f; };
	//
	~Error();
};

