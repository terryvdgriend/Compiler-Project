#include "stdafx.h"
#include "TestIt.h"
#include "TestText.h"


TestIt::TestIt()
{
	list<Error> expectedErrors{};

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
	Run("Identifiers", TestText::GetIdentifiers());
	Run("Identifier undefined/already defined", "**a** is 5 _number_ **b** _number_ **b**", list<string>{"already", "undefined"});

	double elapsed_secs = double(clock() - sttime) / CLOCKS_PER_SEC;
	std::cout << "\r\n\r\nTest finished in: " + to_string(elapsed_secs) + " secs\r\n\r\n";
}

void TestIt::Run(string _name, string _code)
{
	Run(_name, _code, list<string>{});
}


// Expected Errors: lijst met keywords per error die voor MOETEN GAAN komen
// Voorbeeld: 2 errors (bla bla .. undefined .. bla bla .. already defined) worden dus 2 keywords: undefined, already defined
// Komt de error niet, dan krijg je daarvoor weer een error
void TestIt::Run(string _name, string _code, list<string> expectedErrors)
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
	Errors(_name, expectedErrors);
}



void TestIt::Errors(string _name, list<string> expectedErrors)
{
	auto errs = ErrorHandler::getInstance()->getErrors();

	std::cout << string("=============== " + to_string(errs.size() - expectedErrors.size()) + " error(s) for '" + _name + "' ===============\r\n");

	if (!errs.empty())
	{
		for (auto err : errs)
		{
			bool printIt = true;
			for (auto ee : expectedErrors)
			{
				if (err.getName().find(ee) != std::string::npos)
				{
					expectedErrors.remove(ee);
					printIt = false;
					break;
				}
			}
			if (printIt) {
				std::cout << string("     > ");
				err.print();
			}
		}
		std::cout << string("\r\n\r\n");
		ErrorHandler::getInstance()->clearErrors();

	}

	if (expectedErrors.size() != 0)
	{
		std::cout << string("  > Expected errors were not expected: ");
		std::copy(expectedErrors.begin(), expectedErrors.end(),
			std::ostream_iterator<string>(std::cout, ", ")
			);
	}
}

TestIt::~TestIt()
{
}
