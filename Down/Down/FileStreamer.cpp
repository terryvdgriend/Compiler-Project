#include "stdafx.h"
#include "FileStreamer.h"

string FileStreamer::readerFromResource(string filename)
{
	return readerFromResource(filename, "txt");
}

string FileStreamer::readerFromResource(string filename, string ext)
{
	ifstream input_file{ "./" + filename + "." + ext };
	string line;
	string allLines;

	while (getline(input_file, line)) 
	{
		allLines += line + "\n";
	}

	return allLines;
}

string FileStreamer::readerFromPath(string filename)
{
	ifstream input_file{ filename };
	string line;
	string allLines;

	while (getline(input_file, line)) 
	{
		allLines += line + "\n";
	}

	return allLines;
}