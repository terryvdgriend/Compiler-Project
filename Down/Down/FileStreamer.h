#pragma once
#include <iostream>
#include <fstream>
#include <sstream>


class FileStreamer
{
public:
	FileStreamer();
	std::string readerFromPath(std::string path);
	std::string readerFromResource(std::string path);
	~FileStreamer();
};

