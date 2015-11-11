#include "stdafx.h"
#include "FileStreamer.h"


FileStreamer::FileStreamer()
{
}

std::string FileStreamer::readerFromResource(std::string filename)
{
	ifstream input_file{ "./" + filename + ".txt"};

	string line;
	string alllines;
	while (getline(input_file, line)) {
		alllines += line + "\n";
	}
	return alllines;
}

std::string FileStreamer::readerFromPath(std::string filename)
{
	ifstream input_file{ filename };

	string line;
	string alllines;
	while (getline(input_file, line)) {
		alllines += line + "\n";
	}
	return alllines;
}



FileStreamer::~FileStreamer()
{
}
