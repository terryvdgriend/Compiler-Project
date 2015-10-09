// Down.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Tokenizer.h"
#include "Compute.h"
#include "Program.h"
#include "Token.h"
#include "FileStreamer.h"
#include "Format.h"

string getTextFromFile();

int main()
{
	//Declas
	Token::TokenList cTokenList;
	string codefromfile = getTextFromFile();//

	//=========TOKENIZER==============
	Tokenizer tnzr{ Tokenizer() };
	tnzr.createTokenList(cTokenList, codefromfile);


	//=========COMPILER==============
	Compute comp{ Compute(cTokenList) };



	//=========VM==============
	//TODO: meesturen wat je terug krijgt van de compute
	Program prog{ Program() }; 




	//ZI ENDZ
	int inputz = -1;
	std::cin >> inputz;
	return 0;
}


string getTextFromFile()
{
	// vul naam in van de resource, die je wilt testen
	// if / while / etc
	string txtTje = "if";
	//
	string datFile = "./" + txtTje + ".txt";
	FileStreamer fs{ FileStreamer() };
	return fs.reader(datFile);;
}
