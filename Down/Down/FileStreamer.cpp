#include "stdafx.h"
#include "FileStreamer.h"


FileStreamer::FileStreamer()
{
}

std::string FileStreamer::reader(std::string path)
{
	ifstream input_file{ path }; 
	string line;
	string alllines;
	while (getline(input_file, line)) { 
		alllines+= line + "\n";
	}
	return alllines;
}


std::vector<std::string> FileStreamer::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}


std::vector<std::string> FileStreamer::split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

FileStreamer::~FileStreamer()
{
}
