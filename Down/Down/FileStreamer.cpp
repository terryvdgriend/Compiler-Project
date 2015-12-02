#include "stdafx.h"
#include "FileStreamer.h"

string FileStreamer::readerFromResource(string filename)
{
	ifstream input_file{ "./" + filename + ".txt"};
	string line;
	string alllines;

	while (getline(input_file, line)) 
	{
		alllines += line + "\n";
	}

	return alllines;
}

string FileStreamer::readerFromPath(string filename)
{
	ifstream input_file{ filename };
	string line;
	string alllines;

	while (getline(input_file, line)) 
	{
		alllines += line + "\n";
	}

	return alllines;
}