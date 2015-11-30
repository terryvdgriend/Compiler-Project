#pragma once
#include <iostream>
#include <sstream>
#include <vector>

namespace Text{
	int ReadLine();
	void PrintLine(std::string text);
	//void PrintLine(){ PrintLine("\n"); };
	void Print(std::string text);
	std::vector<std::string> Split(const std::string &s, char delim);
};

