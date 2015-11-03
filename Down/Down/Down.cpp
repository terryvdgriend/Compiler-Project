
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
LinkedList RunTokenizer(std::string code, bool print);
LinkedActionList RunCompiler(LinkedList* lToken, bool print);
void RunVM(LinkedActionList lToken);

int main(int argc, const char * argv[])
{
	string code = "";

	//==========IDE=============
	if (!IDEstuff(argc, argv, code))
		return 0;

	//=========TOKENIZER==============
	LinkedList cTokenList = RunTokenizer(code, true);
	if (!ErrorHandler::getInstance()->getErrors().empty())
		return 0;

	//=========COMPILER==============
	LinkedActionList cRunList = RunCompiler(&cTokenList, true);
	if (!ErrorHandler::getInstance()->getErrors().empty())
		return 0;

	//=========VM==============
	RunVM(cRunList);
	if (!ErrorHandler::getInstance()->getErrors().empty())
		std::cerr << ErrorHandler::getInstance()->asJson();


	return 0;
}

LinkedList RunTokenizer(std::string code, bool print)
{
	//=========TOKENIZER==============
	LinkedList cTokenList{};
	Tokenizer tnzr{ Tokenizer() };
	tnzr.createTokenList(cTokenList, code);
	if (print)
		tnzr.printTokenList(cTokenList);

	if (!ErrorHandler::getInstance()->getErrors().empty())
		std::cerr << ErrorHandler::getInstance()->asJson();
	return cTokenList;
}

LinkedActionList RunCompiler(LinkedList* lToken,bool print)
{
	//=========COMPILER==============
	LinkedActionList cRunList{ LinkedActionList() };
	cRunList.add(new DoNothingNode());
	Compute compute{ Compute() };
	compute.ComputeCompile(lToken, &cRunList);
	if (print)
		cRunList.printList();

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
		else 
			return false;
	}
	else 
		return false;
	
	
	cout << outz;
	return false;
}


