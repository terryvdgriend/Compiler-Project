// Down.cpp : Defines the entry point for the console application.
//
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
#include "CompileWhile.h"
#include "DoNothingNode.h"
#include "CompileSingleStatement.h"

//Mogen weg!!
#include "CompileCondition.h"
#include "CompileEquals.h"
#include "CompilePlusMinus.h"
#include "CompileTimesDivideModulo.h"
#include "DoNothingNode.h"

string getTextFromFile();
string getTextFromFile(string filename);
void doDingen(int argc, const char * argv[]);

std::string IDEstuff(int argc, const char * argv[]);

int main(int argc, const char * argv[])
{
	string code = "";

	//code = IDEstuff(argc, argv);
    if(code == "BREAK") {
        return 0;
    }

	////Declas
	LinkedList cTokenList;

	//=========TOKENIZER==============
	Tokenizer tnzr{ Tokenizer() };
	tnzr.createTokenList(cTokenList,getTextFromFile("while.md"));
	tnzr.printTokenList(cTokenList);
    
	if (ErrorHandler::getInstance()->getErrors().empty()){
		//=========COMPILER==============
		
		LinkedActionList cRunList{ LinkedActionList() };
		cRunList.add(new DoNothingNode());

		Compute compute{ Compute() };

		compute.ComputeCompile(&cTokenList, &cRunList);
		cRunList.printList();
		//=========VM==============
		if (ErrorHandler::getInstance()->getErrors().empty()){
					VirtualMachine vm{ VirtualMachine() };
		vm.execute(cRunList);
		}
	}
    
	if (!ErrorHandler::getInstance()->getErrors().empty())
	{
		std::cerr << ErrorHandler::getInstance()->asJson();
	}

	cin >> code;
	
	return 0;
}

std::string IDEstuff(int argc, const char * argv[])
{
	string code = "BREAK";
	if (argc == 3) {
		string option = argv[1];
		string value = argv[2];

		if (option == "-f") {
			// File
			// std::cout << value << std::endl;
			code = getTextFromFile(value);
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
        } else {
            std::cout << "No valid action" << std::endl;
        }
    }
    else {
		std::cout << "Not enough params" << std::endl;
	}
    
	return code;
}

void doDingen(int argc, const char * argv[]){
	//string code = "";

	//if (argc == 3) {
	//	string option = argv[1];
	//	string value = argv[2];

	//	if (option == "-f") {
	//		// File
	//		// std::cout << value << std::endl;
	//		code = getTextFromFile(value);
	//	}
	//	else if (option == "-c") {
	//		// Code
	//		// std::cout << value << std::endl;
	//		code = value;
	//	}
	//	else {
	//		std::cout << "No valid option: " << option << std::endl;
	//		return 0;
	//	}
	//}
	//else {
	//	std::cout << "Not enough params" << std::endl;
	//	return 0;
	//}
	////Declas
	//LinkedList cTokenList;

	////=========TOKENIZER==============
	//Tokenizer tnzr{ Tokenizer() };
	//tnzr.createTokenList(cTokenList, getTextFromFile());
	//tnzr.printTokenList(cTokenList);


	//if (!tnzr.GetTokenError()){
	//	//=========COMPILER==============
	//	
	//LinkedActionList cRunList{ LinkedActionList() };
	//cRunList.add(new DoNothingNode());

	//Compute compute{ Compute() };

	//compute.ComputeCompile(&cTokenList, &cRunList);
	//	cRunList.printList();
	////	//=========VM==============
	////	//TODO: meesturen wat je terug krijgt van de compute
	////Program prog{ Program() };

	//}
	//CompileTimesDivideModulo* condition = new CompileTimesDivideModulo();
}

string getTextFromFile(string fileName) {
	string datFile = fileName;
	FileStreamer fs{ FileStreamer() };
	return fs.reader(datFile);
}


string getTextFromFile()
{
	// vul naam in van de resource, die je wilt testen
	// if / while / etc
	string txtTje = "while";
	//
	string datFile = "./" + txtTje + ".txt";
	FileStreamer fs{ FileStreamer() };
	return fs.reader(datFile);;
}
