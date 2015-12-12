#include "stdafx.h"
#include "TestIt.h"
#include "TestText.h"


TestIt::TestIt()
{
}



void TestIt::RunAll()
{
	std::cout << string("\r\n\r\n=============== BUILD 13.3.7 ===============\r\n\r\n");
	clock_t sttime = clock();

	Run("If Else", fs.readerFromResource("test_ifelse", "md"));
	//Run("Forloop", fs.readerFromResource("test_for", "md"));
	//Run("While loop", fs.readerFromResource("test_while", "md"));
	//Run("Functions", fs.readerFromResource("test_functions", "md"));
	Run("Switch Case", TestText{}.textzz);
	//Run("", fs.readerFromResource("test_", "md"));


	double elapsed_secs = double(clock() - sttime) / CLOCKS_PER_SEC;
	std::cout << "\r\n\r\nTest finished in: " + to_string(elapsed_secs) + " secs\r\n\r\n";
}


//Kan ook public worden, om zelf bepaalde code te testen..
void TestIt::Run(string _name, string _code)
{
	try
	{	
		//=========TOKENIZER==============
		LinkedList* cTokenList{ new LinkedList() };
		Tokenizer tnzr{ Tokenizer() };
		tnzr.createTokenList(*cTokenList, _code);

		//=========COMPILER==============
		LinkedActionList* cRunList{ new LinkedActionList() };
		if (ErrorHandler::getInstance()->getErrors().empty())
		{
			cRunList->add(new DoNothingNode());
			Compute compute{ Compute() };
			compute.ComputeCompile(cTokenList, cRunList);
		}

		//=========VM==============
		if (ErrorHandler::getInstance()->getErrors().empty())
		{
			VirtualMachine vm{ VirtualMachine() };
			vm.execute(*cRunList);
		}
	}
	catch (const exception & ex)
	{
		std::string whut = ex.what();
		ErrorHandler::getInstance()->addThrownError("Try Catch Error: " + whut);
	}
	catch (...)
	{
		ErrorHandler::getInstance()->addThrownError("Try Catch Error: ...");
	}
	Errors(_name);
}

bool TestIt::Errors(string _name)
{
	auto errs = ErrorHandler::getInstance()->getErrors();
	if (!errs.empty())
	{
		std::cout << string("\r\n\r\n=============== " + to_string(errs.size()) + " errors in '" + _name + "' ===============\r\n");
		for (auto err : errs)
		{
			std::cout << string("  > " + err.getName() + "\r\n");
		}
		ErrorHandler::getInstance()->clearErrors();
		return true;
	}
	else
	{

		std::cout << string("=============== No errors in '" + _name + "' ===============\r\n");
		return false;
	}
	return false;
}

TestIt::~TestIt()
{
}
