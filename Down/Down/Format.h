#pragma once
#include <iostream>
#include <fstream>
#include <sstream>

namespace Format{
	std::vector<std::string> split(const std::string &s, char delim);
	std::vector<std::string> split(const std::string &s, char delim, std::vector<std::string> &elems);

}
