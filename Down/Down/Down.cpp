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

int main(int argc, const char* argv[])
{
	string code = "";

	//==============IDE==============
	if (!IDEstuff(argc, argv, code))
	{
		return 0;
	}

	//==============DOWN=============
	runDown(code);

	return 0;
}

void runDown(string code)
{
	const bool PRINT_TOKEN_LIST = false;
	const bool PRINT_COMPILED_LIST = false;

	//==============TOKENIZER========
	shared_ptr<LinkedList> tokenList = runTokenizer(code, PRINT_TOKEN_LIST);

	if (Errors())
	{
		return;
	}

	//==============COMPILER=========
	shared_ptr<LinkedActionList> compiledList = runCompiler(*tokenList, PRINT_COMPILED_LIST);

	if (Errors())
	{
		return;
	}

	//==============VM===============
	runVM(*compiledList);
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

bool Errors()
{
	if (!ErrorHandler::getInstance()->getErrors().empty())
	{
		cerr << ErrorHandler::getInstance()->asJson();

		return true;
	}

	return false;
}

//Return success
bool IDEstuff(int argc, const char* argv[], string& code)
{
	if (argc <= 1 || argc >= 5) // No other options defined yet
	{
		// Alternative code for debugging without the IDE
		code = FileStreamer{}.readerFromResource("custom");

		return true;
	}
	string option = argv[1];
	string outz = "No valid option: " + option + " or arg: " + to_string(argc) + "\n";

	if (argc == 3)
	{
		string value = argv[2];

		if (option == "-f") 
		{
			// File
			FileStreamer fs{};
			code = fs.readerFromPath(value);

			return true;
		}
		else if (option == "-c")
		{
			code = value; // Code
		}
		else
		{
			return false;
		}
	}
	else if (argc == 2)
	{
		if (option == "getTokens")
		{
			outz = Tokenizer().getKeywordsAsJson();
		}
		if (option == "getSnippets")
		{
			outz = Tokenizer().getKeywordsAsJson();
		}
		if (option == "getDingen")
		{
			outz = Tokenizer().getKeywordsAsJson();
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	cout << outz;

	return false;
}