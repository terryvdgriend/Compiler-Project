#include "stdafx.h"
#include "Text.h"

namespace Text
{
	int readLine()
	{
		int inputz;
		cin >> inputz;

		return inputz;
	}

	void printLine(string text)
	{
		cout << text << endl;
	}

	void print(string text)
	{
		cout << text;
	}
};