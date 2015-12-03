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

	// trim from start
	std::string &ltrim(std::string &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
		return s;
	}

	// trim from end
	 std::string &rtrim(std::string &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
		return s;
	}

	// trim from both ends
	std::string &trim(std::string &s) {
		return ltrim(rtrim(s));
	}

};