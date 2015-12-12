#include "stdafx.h"
#include "TestIt.h"
#include "TestText.h"


TestIt::TestIt()
{
}



void TestIt::RunAll()
{
	std::cout << string("\r\n\r\n------ Test started ------\r\n\r\n");
	clock_t sttime = clock();

	//fs.readerFromResource("test_ifelse", "md")
	Run("If Else", TestText::GetIfElse());
	Run("Forloop", TestText::GetFor());
	Run("While loop", TestText::GetWhile());
	Run("Functions", TestText::GetFunctions());
	Run("Switch Case", TestText::GetSwitch());
	

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
