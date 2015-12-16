#pragma once

namespace Text
{
	int readLine();
	void printLine(string text);
	void print(string text);

	vector<string> split(const string& s, char delim);
	string& ltrim(string& s);
	string& rtrim(string& s);
	string& trim(string& s);
};