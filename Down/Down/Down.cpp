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
#include <ctime>
#include "TestIt.h"

//TEMP
#include "TestText.h"

struct IDEargs {
	string code = "";
	bool printCompileList = false;
	bool PrintTokenList = false;
	bool printTime = false;
	bool Test = false;
	bool Build = false;
};


bool IDEstuff(int argc, char * argv[], IDEargs &ideargs);
LinkedList* RunTokenizer(std::string code, bool print);
LinkedActionList* RunCompiler(LinkedList* lToken, bool print);
bool Errors();
void RunVM(LinkedActionList lToken);
clock_t sttime;

int main(int argc, char * argv[])
{
	IDEargs ideargs;
	//==========IDE=============
	if (!IDEstuff(argc, argv, ideargs))
		return 0;
	
	if (ideargs.printTime)
		sttime = clock();

	// =========TEST============
	if (ideargs.Test)
	{
		TestIt().RunAll();
		return 0;
	}

	//=========TOKENIZER==============
	LinkedList cTokenList = *RunTokenizer(ideargs.code, ideargs.PrintTokenList);
	if (Errors())
		return 0;

	//=========COMPILER==============
	LinkedActionList cRunList = *RunCompiler(&cTokenList, ideargs.printCompileList);
	if (Errors())
		return 0;

	//=========VM==============
	if (!ideargs.Build)
		RunVM(cRunList);

	if (Errors())
		return 0;

	if (ideargs.printTime)
	{
		double elapsed_secs = double(clock() - sttime) / CLOCKS_PER_SEC;
		std::cout << "Time elapsed: " + to_string(elapsed_secs);
	}
		

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
		double elapsed_secs = double(clock() - sttime) / CLOCKS_PER_SEC;
		std::cout << "Time elapsed: " + to_string( elapsed_secs);
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
bool IDEstuff(int argc, char * argv[], IDEargs &ideargs)
{
	//Text::PrintLine("COUTNERT:  " + argc);
	if (argc == 1)//andere opties hebben we nog niet
	{
		// Als je hier komt, ben je waarschijnlijk(?) aan het debuggen
		// Dus voor de EZPZ wat fun code.
		ideargs.code = FileStreamer{}.readerFromResource("custom");
		return true;
	}

	string outz = "No valid args\n";
	bool cont = true;

	string value = argv[argc - 1]; //laatste arg = textfile path
	int i = 0;

	while (i != (argc))
	{
		string opt = argv[i];
		//Text::PrintLine("Wazdeze:  " + opt);
		if (opt == "-r" || opt == "--run") {
			// File
			FileStreamer fs{};
			ideargs.code = fs.readerFromPath(value);
		}
		else if (opt == "-t" || opt == "--tokenlist")//Print tokens
		{
			ideargs.PrintTokenList = true;
		}
		else if (opt == "-c" || opt == "--compilelist")//Print runlist
		{
			ideargs.printCompileList = true;
		}
		else if (opt == "--build")
		{
			ideargs.Build = true;
		}
		else if (opt == "--time")
		{
			ideargs.printTime = true;
		}
		else if (opt == "--test")
		{
			ideargs.Test = true;
		}
		else if (opt == "getTokens") {
			outz = Tokenizer().getKeywordsAsJson();
			cont = false;
		}
		else if (opt == "getSnippets") {
			outz = (FileStreamer{}).readerFromResource("Snippets");
			cont = false;
		}
		else if (opt == "getFunctions") {
			outz = Tokenizer().getFunctionsAsJson();
			cont = false;
		}
		else if (opt == "getAll")
		{
			outz = Tokenizer().getFunctionsAsJson();
			outz += Tokenizer().getKeywordsAsJson();
			outz += (FileStreamer{}).readerFromResource("Snippets");
			return false;
		}
		i++;
	}

	if (!cont)
	{
		cout << outz;
	}
	return cont;
}

