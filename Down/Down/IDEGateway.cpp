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

bool IDEGateway::handleIDEArguments(int argCounter, char* argValues[])
{
	// Return: true  -> Proceed with the rest of the code (most probable)
	// Return: false -> Stop after the execution of this method (used to get, for instance, snippets and tokens)
	FileStreamer fileStreamer;

	if (argCounter == 1)
	{
		code = fileStreamer.readerFromResource("custom");

		return true;
	}
	Tokenizer tokenizer;

	string output = "No valid args\n";
	bool cont = true;

	string value = argValues[argCounter - 1]; // Last argument = textfile path
	int i = 0;

	while (i != argCounter)
	{
		string option = argValues[i];

		if (option == "-r" || option == "-run")
		{
			code = fileStreamer.readerFromPath(value);
		}
		else if (option == "-t" || option == "--tokenlist")
		{
			printTokenList = true;
		}
		else if (option == "-c" || option == "--compilelist")
		{
			printCompiledList = true;
		}
		else if (option == "--time")
		{
			printElapsedTime = true;
		}
		else if (option == "--build")
		{
			build = true;
		}
		else if (option == "--test")
		{
			runTest = true;
		}
		else if (option == "getTokens")
		{
			output = tokenizer.getKeywordsAsJson();
			cont = false;
		}
		else if (option == "getSnippets")
		{
			output = fileStreamer.readerFromResource("Snippets");
			cont = false;
		}
		else if (option == "getFunctions")
		{
			output = tokenizer.getFunctionsAsJson();
			cont = false;
		}
		else if (option == "getAll")
		{
			output = tokenizer.getFunctionsAsJson();
			output += tokenizer.getKeywordsAsJson();
			output += fileStreamer.readerFromResource("Snippets");

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