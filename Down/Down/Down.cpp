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

//Mogen weg!!
#include "CompileCondition.h"
#include "DoNothingNode.h"

string getTextFromFile();

int main()
{
	//Declas
	LinkedList cTokenList;
	string codefromfile = getTextFromFile();//

	//=========TOKENIZER==============
	Tokenizer tnzr{ Tokenizer() };
	tnzr.createTokenList(cTokenList, codefromfile);
	tnzr.printTokenList(cTokenList);

	//=========COMPILE CONDITION======
	CompileCondition condition = CompileCondition();
	LinkedActionList actionList = LinkedActionList();
	DoNothingNode node1 = DoNothingNode();
	actionList.insertLast(&node1);
	condition.Compile(cTokenList, *cTokenList.first, *cTokenList.last, actionList, node1);
	actionList.printList();

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
	string txtTje = "condition";
	//
	string datFile = "./" + txtTje + ".txt";
	FileStreamer fs{ FileStreamer() };
	return fs.reader(datFile);;
}
