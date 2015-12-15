#pragma once

class FileStreamer
{
	public:
		string readerFromPath(string path);
		string readerFromResource(string path);
		string readerFromResource(string path, string ext);
};