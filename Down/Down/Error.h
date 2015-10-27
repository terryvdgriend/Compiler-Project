#pragma once
 
class Error
{
private:
	std::string name;
public:
	enum type { tokenizer, compiler, vm };
	Error(std::string _name, type type);
	~Error();
};

