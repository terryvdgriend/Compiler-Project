// Down.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Tokenizer.h"
#include "Token.h"
#include "FileStreamer.h"
#include "Format.h"

int main()
{
	//Declas
	Token::TokenList cTokenList;
	string codefromfile = getTextFromFile();//

	//=========TOKENIZER==============
	Tokenizer tnzr{ Tokenizer() };
	tnzr.createTokenList(cTokenList, codefromfile);


	//=========COMPILER==============




	//=========VM==============





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
