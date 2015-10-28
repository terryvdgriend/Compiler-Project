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




FileStreamer::~FileStreamer()
{
}
