#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

namespace Text{
	int ReadLine();
	void PrintLine(std::string text);
	//void PrintLine(){ PrintLine("\n"); };
	void Print(std::string text);
	std::vector<std::string> Split(const std::string &s, char delim);
	std::string &ltrim(std::string &s);
	std::string &rtrim(std::string &s);
	std::string &trim(std::string &s);
};

