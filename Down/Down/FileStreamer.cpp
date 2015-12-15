#include "stdafx.h"
#include "FileStreamer.h"


FileStreamer::FileStreamer()
{
}

//Extension type .txt / Als je iets anders wilt kies dan de overload
std::string FileStreamer::readerFromResource(std::string filename)
{
	return readerFromResource(filename, "txt");
}

std::string FileStreamer::readerFromResource(std::string filename, std::string ext)
{
	ifstream input_file{ "./" + filename + "." + ext };

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
