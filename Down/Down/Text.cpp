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

	vector<string> split(const string &s, char delim) 
	{
		stringstream ss(s);
		string item;
		vector<string> elems;

		while (getline(ss, item, delim)) 
		{
			elems.push_back(item);
		}

		return elems;
	}

	// Trim from start
	string &ltrim(string &s) 
	{
		s.erase(s.begin(), find_if(s.begin(), s.end(), std::not1(ptr_fun<int, int>(std::isspace))));

		return s;
	}

	// Trim from end
	 std::string &rtrim(std::string &s) 
	 {
		s.erase(find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(), s.end());

		return s;
	}

	// Trim from both ends
	string &trim(string &s) 
	{
		return ltrim(rtrim(s));
	}
};