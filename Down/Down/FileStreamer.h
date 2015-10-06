#pragma once
#include <iostream>
#include <fstream>
#include <sstream>


class FileStreamer
{
public:
	FileStreamer();
	std::string reader(std::string path);
	std::vector<std::string> split(const std::string &s, char delim);
	std::vector<std::string> split(const std::string &s, char delim, std::vector<std::string> &elems);
	~FileStreamer();
};

