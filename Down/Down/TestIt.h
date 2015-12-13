#pragma once
#include "LinkedList.h"
#include "FileStreamer.h"
#include "Compute.h"
#include "DoNothingNode.h"
#include <ctime>

class TestIt
{
private:
	FileStreamer fs{};
	
	bool Errors(string _name);
public:
	TestIt();
	void RunAll();
	void Run(string _name, string _code);
	void Run(string _name, string _code, list<string> _expectedErrors);
	~TestIt();
};

