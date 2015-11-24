
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>

//Laten staan voor de apple gebruikert
#ifdef _WIN32
#include <crtdbg.h>
#endif

#include "stdafx.h"
#include "Token.h"
#include "Tokenizer.h"
#include "Compute.h"
#include "Token.h"
#include "LinkedList.h"
#include "FileStreamer.h"
#include "Format.h"
#include "DoNothingNode.h"

bool IDEstuff(int argc, const char * argv[], std::string &code);
LinkedList* RunTokenizer(std::string code, bool print);
LinkedActionList* RunCompiler(LinkedList* lToken, bool print);
bool Errors();
void RunVM(LinkedActionList lToken);

int main(int argc, const char * argv[])
{
	//std::cerr << "WHUT?!";
	string code = "";
	//==========IDE=============
	if (!IDEstuff(argc, argv, code))
		return 0;


	//=========TOKENIZER==============
	LinkedList cTokenList = *RunTokenizer(code, false);
	if (Errors())
		return 0;

	//=========COMPILER==============
	LinkedActionList cRunList = *RunCompiler(&cTokenList, false);
	if (Errors())
		return 0;

	//=========VM==============
	RunVM(cRunList);
	if (Errors())
		return 0;
	


	return 0;
}

LinkedList* RunTokenizer(std::string code, bool print)
{
	//=========TOKENIZER==============
	LinkedList* cTokenList{ new LinkedList() };
	Tokenizer tnzr{ Tokenizer() };
	tnzr.createTokenList(*cTokenList, code);
	if (print)
		tnzr.printTokenList(*cTokenList);

	return cTokenList;
}

bool Errors()
{
	if (!ErrorHandler::getInstance()->getErrors().empty())
	{
		std::cerr << ErrorHandler::getInstance()->asJson();
		return true;
	}
	return false;
}

shared_ptr<LinkedActionList> RunCompiler(LinkedList* lToken, bool print)
{
	//=========COMPILER==============
	unique_ptr<Compute> compute = make_unique<Compute>();
	shared_ptr<LinkedActionList> cRunList = compute.computeCompile(lToken);
	
	if (print)
	{
		cRunList->printList();
	}

	return cRunList;
}

void RunVM(LinkedActionList cRunList)
{
	//=========VM==============
	VirtualMachine vm{ VirtualMachine() };
	vm.execute(cRunList);


	if (!ErrorHandler::getInstance()->getErrors().empty())
		std::cerr << ErrorHandler::getInstance()->asJson();

}





//Return success
bool IDEstuff(int argc, const char * argv[], std::string &code)
{
	if (argc <= 1 || argc >= 5)//andere opties hebben we nog niet
	{
		// Als je hier komt, ben je waarschijnlijk(?) aan het debuggen
		// Dus voor de EZPZ wat fun code.
		code = FileStreamer{}.readerFromResource("custom");
		return true;
	}

	string option = argv[1];
	string outz = "No valid option: " + option + " or arg: " + to_string(argc) + "\n";

	if (argc == 3)
	{
		string value = argv[2];
		if (option == "-f") {
			// File
			FileStreamer fs{};
			code = fs.readerFromPath(value);
			return true;
		}
		else if (option == "-c")
			code = value; // Code
		else
			return false;
	}
	else if (argc == 2)
	{
		if (option == "getTokens")
			outz = Tokenizer().getKeywordsAsJson();
		if (option == "getSnippets")
			outz = Tokenizer().getKeywordsAsJson();
		if (option == "getDingen")
			outz = Tokenizer().getKeywordsAsJson();
		else
			return false;
	}
	else
		return false;


	cout << outz;
	return false;
}


