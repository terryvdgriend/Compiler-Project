#include "stdafx.h"
#include "TestDown.h"
#include "Compute.h"
#include "LinkedActionList.h"
#include "LinkedTokenList.h"
#include "Tokenizer.h"
#include "TestCode.h"
#include "VirtualMachine.h"

void TestDown::runAll()
{
	cout << "\r\n\r\n------ Test started ------\r\n\r\n";
	clock_t sttime = clock();

	run("If Else", TestCode::GetIfElse());
	run("Forloop", TestCode::GetFor());
	run("While loop", TestCode::GetWhile());
	run("Functions", TestCode::GetFunctions());
	run("Switch Case", TestCode::GetSwitch());
	run("Identifiers", TestCode::GetIdentifiers());
	run("Identifier undefined/already defined", "**a** is 5 _number_ **b** _number_ **b**", list<string>{"already", "undefined"});

	double elapsed_secs = double(clock() - sttime) / CLOCKS_PER_SEC;
	cout << "\r\n\r\nTest finished in: " + to_string(elapsed_secs) + " secs\r\n\r\n";
}

void TestDown::run(string _name, string _code)
{
	run(_name, _code, list<string>{});
}

// Expected Errors: lijst met keywords per error die voor MOETEN GAAN komen
// Voorbeeld: 2 errors (bla bla .. undefined .. bla bla .. already defined) worden dus 2 keywords: undefined, already defined
// Komt de error niet, dan krijg je daarvoor weer een error
void TestDown::run(string _name, string _code, list<string> expectedErrors)
{
	shared_ptr<LinkedTokenList> tokenList = nullptr;
	shared_ptr<LinkedActionList> compiledList = nullptr;

	try
	{
		//=========TOKENIZER==============
		tokenList = make_shared<LinkedTokenList>();
		Tokenizer tokenizer;
		tokenizer.createTokenList(tokenList, _code);

		//=========COMPILER==============
		if (ErrorHandler::getInstance()->getErrors().empty())
		{
			Compute compute;
			compiledList = compute.computeCompile(tokenList);
		}

		//=========VM==============
		if (ErrorHandler::getInstance()->getErrors().empty())
		{
			VirtualMachine vm;
			vm.execute(compiledList);
		}
	}
	catch (const exception& e)
	{
		string whut = e.what();
		ErrorHandler::getInstance()->addThrownError("Try Catch Error: " + whut);
	}
	catch (...)
	{
		ErrorHandler::getInstance()->addThrownError("Try Catch Error: ...");
		cleanup(tokenList, compiledList);
	}
	errors(_name, expectedErrors);
	cleanup(tokenList, compiledList);
}

void TestDown::errors(string _name, list<string> expectedErrors)
{
	list<shared_ptr<Error>> errors = ErrorHandler::getInstance()->getErrors();

	cout << string("=============== " + to_string(errors.size() - expectedErrors.size()) + " error(s) for '" + _name + "' ===============\r\n");

	if (!errors.empty())
	{
		for (shared_ptr<Error> error : errors)
		{
			bool printIt = true;

			for (string ee : expectedErrors)
			{
				if (error->getName().find(ee) != string::npos)
				{
					expectedErrors.remove(ee);
					printIt = false;

					break;
				}
			}

			if (printIt) 
			{
				cout << string("     > ");
				error->print();
			}
		}
		cout << string("\r\n\r\n");
		ErrorHandler::getInstance()->clearErrors();

	}

	if (expectedErrors.size() != 0)
	{
		cout << string("  > Expected errors were not expected: ");
		copy(expectedErrors.begin(), expectedErrors.end(), ostream_iterator<string>(cout, ", "));
	}
}

void TestDown::cleanup(shared_ptr<LinkedTokenList>& tokenList, shared_ptr<LinkedActionList>& compiledList)
{
	if (compiledList != nullptr)
	{
		shared_ptr<ActionNode> nextNode = compiledList->getFirst();
		compiledList.reset();

		while (nextNode)
		{
			nextNode = nextNode->getNext();
		}
	}

	if (tokenList != nullptr)
	{
		shared_ptr<Token> next = tokenList->getFirst();
		tokenList.reset();

		while (next)
		{
			next = next->getNext();
		}
	}
}