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

bool IDEstuff(int argc, char * argv[], std::string &code, bool &PT, bool &PC, bool &BUILD, bool &TIME, bool &TEST);
LinkedList* RunTokenizer(std::string code, bool print);
LinkedActionList* RunCompiler(LinkedList* lToken, bool print);
bool Errors();
void RunVM(LinkedActionList lToken);

int main(int argc, char * argv[])
{
	string code = "";

	//TODO: onderstaande 1 klasse van maken met deze waardes.
	bool C = false;
	bool T = false;
	bool TIME = false;
	bool TEST = false;
	bool BUILD = false;

	//==========IDE=============
	if (!IDEstuff(argc, argv, code, T, C, BUILD, TIME, TEST))
		return 0;

	// =========TEST============
	if (TEST)
	{
		//(1) Test runnen
		//..
		//(2) Errors terug geven, thats it
		std::cerr << "========== Test runned with x errors ============";
		Errors();
		return 0;
	}

	//=========TOKENIZER==============
	LinkedList cTokenList = *RunTokenizer(code, T);
	if (Errors())
		return 0;

	//=========COMPILER==============
	LinkedActionList cRunList = *RunCompiler(&cTokenList, C);
	if (Errors())
		return 0;

	//=========VM==============
	if (!BUILD)
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
bool IDEstuff(int argc, char * argv[], std::string &code, bool &PT, bool &PC, bool &BUILD, bool &TIME, bool &TEST)
{
	//Text::PrintLine("COUTNERT:  " + argc);
	if (argc == 1)//andere opties hebben we nog niet
	{
		// Als je hier komt, ben je waarschijnlijk(?) aan het debuggen
		// Dus voor de EZPZ wat fun code.
		code = FileStreamer{}.readerFromResource("custom");
		return true;
	}

	//string option = argv[1];
	string outz = "No valid args\n";
	bool cont = true;

	string value = argv[argc - 1]; //laatste arg = textfile path
	int i = 0;

	while (i != (argc))
	{
		string opt = argv[i];
		//Text::PrintLine("Wazdeze:  " + opt);
		if (opt == "-r") {
			// File
			FileStreamer fs{};
			code = fs.readerFromPath(value);

		}
		if (opt == "-t")//Print tokens
		{
			PT = true;
		}
		if (opt == "-c")//Print runlist
		{
			PC = true;
		}
		if (opt == "-build")//build tokens
		{
			BUILD = true;
		}
		if (opt == "-time")
		{
			TIME = true;
		}
		if (opt == "-test")
		{
			TEST = true;
		}
		if (opt == "getTokens") {
			outz = Tokenizer().getKeywordsAsJson();
			cont = false;
		}
		if (opt == "getSnippets") {
			outz = (FileStreamer{}).readerFromResource("Snippets");
			cont = false;
		}
		if (opt == "getFunctions") {
			outz = Tokenizer().getFunctionsAsJson();
			cont = false;
		}
		if (opt == "getAll")
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

