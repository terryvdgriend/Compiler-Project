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

bool IDEstuff(int argc, const char * argv[], std::string &code, bool &T, bool &C);
LinkedList* RunTokenizer(std::string code, bool print);
LinkedActionList* RunCompiler(LinkedList* lToken, bool print);
bool Errors();
void RunVM(LinkedActionList lToken);

int main(int argc, const char * argv[])
{	
	//std::cerr << "WHUT?!";
	string code = "";
	bool C = false;
	bool T = false;
	//==========IDE=============
	if (!IDEstuff(argc, argv, code,T,C))
		return 0;


	//=========TOKENIZER==============
	LinkedList cTokenList = *RunTokenizer(code, T);
	if (Errors())
		return 0;

	//=========COMPILER==============
	LinkedActionList cRunList = *RunCompiler(&cTokenList, C);
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

LinkedActionList* RunCompiler(LinkedList* lToken, bool print)
{
	//=========COMPILER==============
	LinkedActionList* cRunList{ new LinkedActionList() };
	cRunList->add(new DoNothingNode());
	Compute compute{ Compute() };
	compute.ComputeCompile(lToken, cRunList);
	if (print)
		cRunList->printList();

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





//Return: true -> ga verder met rest van code (meeste gevallen)
//Return: false -> stop na deze functie (voor dingen zoals getTokens)
bool IDEstuff(int argc, const char * argv[], std::string &code, bool &T , bool &C)
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
		std::vector<std::string>  options = Text::Split(option, '-');
		for (std::vector<std::string>::iterator it = options.begin(); it != options.end(); ++it)
		{
			string opt = Text::trim(*it);
			/* std::cout << *it; ... */
			if (opt == "r") {
				// File
				FileStreamer fs{};
				code = fs.readerFromPath(value);
			}
			if (opt == "t")//Print tokens
				T = true;
			if (opt == "c")//Print runlist
				C = true;
		}
		return true;
	}
	else if (argc == 2)
	{
		if (option == "getTokens")
			outz = Tokenizer().getKeywordsAsJson();
		else if (option == "getSnippets")
			outz = (FileStreamer{}).readerFromResource("Snippets");
		else if (option == "getFunctions")
			outz = Tokenizer().getFunctionsAsJson();
		else
			return false;
	}
	else
		return false;


	cout << outz;
	return false;
}

