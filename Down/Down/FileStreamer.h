#pragma once
#include <iostream>
#include <fstream>
#include <sstream>


class FileStreamer
{
public:
	FileStreamer();
	std::string reader(std::string path);
	~FileStreamer();
};

