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
	
	void Errors(string _name, list<string> expectedErrors);
public:
	TestIt();
	void RunAll();
	void Run(string _name, string _code);
	void Run(string _name, string _code, list<string> _expectedErrors);
	~TestIt();
};

