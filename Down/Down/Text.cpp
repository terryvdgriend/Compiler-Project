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
};