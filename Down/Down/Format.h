#pragma once

namespace Format
{
	vector<string> split(const string& s, char delim);
	vector<string> split(const string& s, char delim, vector<string>& elems);
}