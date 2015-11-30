#include "stdafx.h"
#include "Text.h"


namespace Text{
	int ReadLine()
	{
		int inputz;
		std::cin >> inputz;
		return inputz;
	}

	void PrintLine(std::string text)
	{
		std::cout << text << "\n";
	}

	void Print(std::string text)
	{
		std::cout << text;
	}

	std::vector<std::string> Split(const std::string &s, char delim) {
		std::stringstream ss(s);
		std::string item;
		std::vector<std::string> elems;
		while (std::getline(ss, item, delim)) {
			elems.push_back(item);
		}
		return elems;
	}

};