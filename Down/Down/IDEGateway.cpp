#include "stdafx.h"
#include "IDEGateway.h"
#include "FileStreamer.h"
#include "Tokenizer.h"

IDEGateway::IDEGateway()
{
	code				= "";
	printTokenList		= false;
	printCompiledList	= false;
	printElapsedTime	= false;
	build				= false;
	runTest				= false;
}

bool IDEGateway::handleIDEArguments(int argCounter, char* argv[])
{
	// Return: true  -> Proceed with the rest of the code (most probable)
	// Return: false -> Stop after the execution of this method (used to get, for instance, snippets and tokens)
	FileStreamer fileStramer;
	Tokenizer tokenizer;

	if (argCounter == 1)
	{
		code = fileStramer.readerFromResource("custom");

		return true;
	}
	string output = "No valid args\n";
	bool cont = true;

	string value = argv[argCounter - 1]; // Last argument = textfile path
	int i = 0;

	while (i != argCounter)
	{
		string opt = argv[i];

		if (opt == "-r" || opt == "-run")
		{
			code = fileStramer.readerFromPath(value);
		}
		else if (opt == "-t" || opt == "-tokenlist")
		{
			printTokenList = true;
		}
		else if (opt == "-c" || opt == "-compilelist")
		{
			printCompiledList = true;
		}
		else if (opt == "-time")
		{
			printElapsedTime = true;
		}
		else if (opt == "-build")
		{
			build = true;
		}
		else if (opt == "-test")
		{
			runTest = true;
		}
		else if (opt == "getTokens")
		{
			output = tokenizer.getKeywordsAsJson();
			cont = false;
		}
		else if (opt == "getSnippets")
		{
			output = fileStramer.readerFromResource("Snippets");
			cont = false;
		}
		else if (opt == "getFunctions")
		{
			output = tokenizer.getFunctionsAsJson();
			cont = false;
		}
		else if (opt == "getAll")
		{
			output = tokenizer.getFunctionsAsJson();
			output += tokenizer.getKeywordsAsJson();
			output += fileStramer.readerFromResource("Snippets");

			return false;
		}
		i++;
	}

	if (!cont)
	{
		cout << output;
	}

	return cont;
}

string IDEGateway::getCode()
{
	return code;
}

bool IDEGateway::doPrintTokenList()
{
	return printTokenList;
}

bool IDEGateway::doPrintCompiledList()
{
	return printCompiledList;
}

bool IDEGateway::doPrintElapsedTime()
{
	return printElapsedTime;
}

bool IDEGateway::doBuild()
{
	return build;
}

bool IDEGateway::doRunTest()
{
	return runTest;
}