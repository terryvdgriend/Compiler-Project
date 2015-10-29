// Down.cpp : Defines the entry point for the console application.
//
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "stdafx.h"
#include "Token.h"
#include "Tokenizer.h"
#include "Compute.h"
#include "Program.h"
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

int main(int argc, const char * argv[])
{
	string code = "";

	if (argc == 3) {
		string option = "-f";//argv[1];
		string value = "if";//argv[2];

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
	else {
		std::cout << "Not enough params" << std::endl;
		return 0;
	}
	////Declas
	LinkedList cTokenList;

	//=========TOKENIZER==============
	Tokenizer tnzr{ Tokenizer() };
	tnzr.createTokenList(cTokenList,code);
	tnzr.printTokenList(cTokenList);

	if (!tnzr.GetTokenError()){
		//=========COMPILER==============
		
		LinkedActionList cRunList{ LinkedActionList() };
		cRunList.add(new DoNothingNode());

		Compute compute{ Compute() };

		compute.ComputeCompile(&cTokenList, &cRunList);
		cRunList.printList();
		//=========VM==============
		//TODO: meesturen wat je terug krijgt van de compute
	
		Program prog{ Program() };
	}
	if (!ErrorHandler::getInstance()->getErrors().empty())
	{
		cout << "ERRORS! \n";
		for (Error e : ErrorHandler::getInstance()->getErrors()){
			cout << e.getName() << " \n";
		}
	}
	cin >> code;
	return 0;
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
