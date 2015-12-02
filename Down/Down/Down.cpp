#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>

//Laten staan voor de apple gebruikert
#ifdef _WIN32
#include <crtdbg.h>
#endif

#include "stdafx.h"
#include "Tokenizer.h"
#include "Compute.h"
#include "VirtualMachine.h"
#include "LinkedList.h"
#include "FileStreamer.h"
#include "Format.h"

int runDown(string& code, bool& printTokenList, bool& printCompiledList);
shared_ptr<LinkedList> runTokenizer(string code, bool printTokenList);
shared_ptr<LinkedActionList> runCompiler(LinkedList& tokenList, bool printCompiledList);
void runVM(LinkedActionList& cRunList);
bool errors();
bool ideStuff(int argc, char* argv[], string& code, bool& printTokenList, bool& printCompiledList);

int main(int argc, char * argv[])
{
	string code = "";
	bool PRINT_TOKEN_LIST = false;
	bool PRINT_COMPILED_LIST = false;

	//==============IDE==============
	if (!ideStuff(argc, argv, code, PRINT_TOKEN_LIST, PRINT_COMPILED_LIST))
	{
		return 0;
	}

	//==============DOWN=============
	return runDown(code, PRINT_TOKEN_LIST, PRINT_COMPILED_LIST);;
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
	shared_ptr<LinkedActionList> compiledList = runCompiler(*tokenList, printCompiledList);

	if (errors())
	{
		return - 1;
	}

	//==============VM===============
	runVM(*compiledList);

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
	tokenizer->createTokenList(*tokenList, code);

	if (printTokenList)
	{
		tokenizer->printTokenList(*tokenList);
	}

	return tokenList;
}

shared_ptr<LinkedActionList> runCompiler(LinkedList& tokenList, bool printCompiledList)
{
	unique_ptr<Compute> compute = make_unique<Compute>();
	shared_ptr<LinkedActionList> compiledList = compute->computeCompile(tokenList);

	if (printCompiledList)
	{
		compiledList->printList();
	}

	return compiledList;
}

void runVM(LinkedActionList& cRunList)
{
	unique_ptr<VirtualMachine> vm = make_unique<VirtualMachine>();
	vm->execute(cRunList);

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
bool ideStuff(int argc, char* argv[], string& code, bool& printTokenList, bool& printCompiledList)
{
	unique_ptr<FileStreamer> fileStramer = make_unique<FileStreamer>();
	unique_ptr<Tokenizer> tokenizer = make_unique<Tokenizer>();

	if (argc == 1)
	{
		code = fileStramer->readerFromResource("custom");

		return true;
	}
	string outz = "No valid args\n";
	bool cont = true;

	string value = argv[argc - 1]; // Last argument = textfile path
	int i = 0;

	while (i != (argc))
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
			outz = tokenizer->getKeywordsAsJson();
			cont = false;
		}

		if (opt == "getSnippets") 
		{
			outz = fileStramer->readerFromResource("Snippets");
			cont = false;
		}

		if (opt == "getFunctions") 
		{
			outz = tokenizer->getFunctionsAsJson();
			cont = false;
		}

		if (opt == "getAll")
		{
			outz = tokenizer->getFunctionsAsJson();
			outz += tokenizer->getKeywordsAsJson();
			outz += fileStramer->readerFromResource("Snippets");

			return false;
		}
		i++;
	}

	if (!cont)
	{
		cout << outz;
	}

	return cont;
}