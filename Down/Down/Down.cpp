// Down.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Tokenizer.h"
#include "Compute.h"
#include "Program.h"
#include "Token.h"
#include "LinkedList.h"
#include "FileStreamer.h"
#include "Format.h"

#include "CompileFactory.h"

string getTextFromFile();

int main()
{
	//DIE FACTORY TAST M8!!!
	CompileFactory FACKtory{};
	Compiler * CUMpiler =  FACKtory.CreateCompileStatement(Token::IF);
	//
	CUMpiler->asd = 14;;
	Compiler * CUMpiler2 = FACKtory.CreateCompileStatement(Token::IF);


	//Declas
	LinkedList cTokenList;
	string codefromfile = getTextFromFile();//

	//=========TOKENIZER==============
	Tokenizer tnzr{ Tokenizer() };
	tnzr.createTokenList(cTokenList, codefromfile);
	tnzr.printTokenList(cTokenList);

	if (!tnzr.GetTokenError()){
		//=========COMPILER==============
		//Compute comp{ Compute(cTokenList) };



		//=========VM==============
		//TODO: meesturen wat je terug krijgt van de compute
		Program prog{ Program() };

	}




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
