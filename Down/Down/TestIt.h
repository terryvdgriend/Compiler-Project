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
	void Run(string _name, string _code);
	bool Errors(string _name);
public:
	TestIt();
	void RunAll();
	~TestIt();
};

