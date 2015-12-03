#include "stdafx.h"
#include "Compute.h"
#include "FileStreamer.h"
#include "Format.h"
#include "LinkedList.h"
#include "Tokenizer.h"
#include "VirtualMachine.h"

#define _CRTDBG_MAP_ALLOC

int runDown(string& code, bool& printTokenList, bool& printCompiledList);
shared_ptr<LinkedList> runTokenizer(string code, bool printTokenList);
shared_ptr<LinkedActionList> runCompiler(shared_ptr<LinkedList>&, bool printCompiledList);
void runVirtualMachine(shared_ptr<LinkedActionList>& compiledList);
bool errors();
bool ideStuff(int argCounter, char* argv[], string& code, bool& printTokenList, bool& printCompiledList);

int main(int argCounter, char* argv[])
{
	string code = "";
	bool printTokenList = false;
	bool printCompiledList = false;

	//==============IDE==============
	if (!ideStuff(argCounter, argv, code, printTokenList, printCompiledList))
	{
		return 0;
	}

	//==============DOWN=============
	return runDown(code, printTokenList, printCompiledList);;
}

int runDown(string& code, bool& printTokenList, bool& printCompiledList)
{
	//==============TOKENIZER========
	shared_ptr<LinkedList> tokenList = runTokenizer(code, printTokenList);

	if (errors())
	{
		return -1;
	}

	//==============COMPILER=========
	shared_ptr<LinkedActionList> compiledList = runCompiler(tokenList, printCompiledList);

	if (errors())
	{
		return -1;
	}

	//==============VM===============
	runVirtualMachine(compiledList);

	if (errors())
	{
		return -1;
	}

	return 0;
}

shared_ptr<LinkedList> runTokenizer(string code, bool printTokenList)
{
	shared_ptr<LinkedList> tokenList = make_shared<LinkedList>();
	unique_ptr<Tokenizer> tokenizer = make_unique<Tokenizer>();
	tokenizer->createTokenList(tokenList, code);

	if (printTokenList)
	{
		tokenizer->printTokenList(tokenList);
	}

	return tokenList;
}

shared_ptr<LinkedActionList> runCompiler(shared_ptr<LinkedList>& tokenList, bool printCompiledList)
{
	unique_ptr<Compute> compute = make_unique<Compute>();
	shared_ptr<LinkedActionList> compiledList = compute->computeCompile(tokenList);

	if (printCompiledList)
	{
		compiledList->printList();
	}

	return compiledList;
}

void runVirtualMachine(shared_ptr<LinkedActionList>& compiledList)
{
	shared_ptr<VirtualMachine> virtualMachine = make_shared<VirtualMachine>();
	virtualMachine->execute(compiledList);

	if (!ErrorHandler::getInstance()->getErrors().empty())
	{
		cerr << ErrorHandler::getInstance()->asJson();
	}
}

bool errors()
{
	if (!ErrorHandler::getInstance()->getErrors().empty())
	{
		cerr << ErrorHandler::getInstance()->asJson();

		return true;
	}

	return false;
}

// Return: true  -> Proceed with the rest of the code (most probable)
// Return: false -> Stop after the execution of this mehod (used to get, for instane, snippets and tokens
bool ideStuff(int argCounter, char* argv[], string& code, bool& printTokenList, bool& printCompiledList)
{
	unique_ptr<FileStreamer> fileStramer = make_unique<FileStreamer>();
	unique_ptr<Tokenizer> tokenizer = make_unique<Tokenizer>();

	if (argCounter == 1)
	{
		code = fileStramer->readerFromResource("custom");

		return true;
	}
	string output = "No valid args\n";
	bool cont = true;

	string value = argv[argCounter - 1]; // Last argument = textfile path
	int i = 0;

	while (i != (argCounter))
	{
		string opt = argv[i];

		if (opt == "-r") 
		{
			code = fileStramer->readerFromPath(value);
		}

		if (opt == "-t") // Print tokens
		{
			printTokenList = true;
		}

		if (opt == "-c") // Print runlist
		{
			printCompiledList = true;
		}

		if (opt == "getTokens") 
		{
			output = tokenizer->getKeywordsAsJson();
			cont = false;
		}

		if (opt == "getSnippets") 
		{
			output = fileStramer->readerFromResource("Snippets");
			cont = false;
		}

		if (opt == "getFunctions") 
		{
			output = tokenizer->getFunctionsAsJson();
			cont = false;
		}

		if (opt == "getAll")
		{
			output = tokenizer->getFunctionsAsJson();
			output += tokenizer->getKeywordsAsJson();
			output += fileStramer->readerFromResource("Snippets");

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