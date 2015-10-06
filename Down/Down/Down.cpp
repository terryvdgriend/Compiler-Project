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
	cout << "so it begins..." << std::endl;

	// vul naam in van de resource, die je wilt testen
	// if / while / etc
	string txtTje = "if"; 
	string datFile = "./" + txtTje + ".txt";

	//Declas
	FileStreamer fs{ FileStreamer() };
	Tokenizer tnzr{ Tokenizer() };
	Token::TokenList cTokenList;

	
	
	//Lezen van code uit file
	string codefromfile = fs.reader(datFile);
	vector<string> splitCode = Format::split(codefromfile, '\n');

	//code doorgeven aan de Tokenizert
	tnzr.createTokenList(cTokenList, splitCode);

	int inputz = -1;
	std::cin >> inputz;
	return 0;
}

