
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

std::string IDEstuff(int argc, const char * argv[]);
LinkedList RunTokenizer(std::string code, bool print);
LinkedActionList RunCompiler(LinkedList* lToken, bool print);
void RunVM(LinkedActionList lToken);

int main(int argc, const char * argv[])
{
	string code = "";

	//==========IDE=============
	code = IDEstuff(argc, argv);
	if (code == "BREAK") {
		return 0;
	}

	//=========TOKENIZER==============
	LinkedList cTokenList = RunTokenizer(code, false);
	if (!ErrorHandler::getInstance()->getErrors().empty())
		return 0;

	//=========COMPILER==============
	LinkedActionList cRunList = RunCompiler(&cTokenList, false);
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






std::string IDEstuff(int argc, const char * argv[])
{
	string code = "BREAK";
	if (argc == 3) {
		string option = argv[1];
		string value = argv[2];

		if (option == "-f") {
			// File
			FileStreamer fs{};
			code = fs.readerFromPath(value);
		}
		else if (option == "-c") {
			// Code
			// std::cout << value << std::endl;
			code = value;
		}
		else {
			std::cout << "No valid option: " << option << std::endl;
			return 0;
		}
	}
	else if (argc == 2) {
		string action = argv[1];
		if (action == "getTokens") {
			std::cout << Tokenizer().getKeywordsAsJson();
		}
		else {
			std::cout << "No valid action" << std::endl;
		}
	}
	else {
		std::cout << "Not enough params" << std::endl;
	}

	return code;
}


