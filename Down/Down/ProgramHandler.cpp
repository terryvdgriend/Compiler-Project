#include "stdafx.h"
#include "ProgramHandler.h"
#include "Compute.h"
#include "TestDown.h"
#include "Tokenizer.h"
#include "VirtualMachine.h"

int ProgramHandler::runProgram(int argCounter, char* argValues[])
{
	IDEGateway ideGateway;

	//==============IDE==============
	if (!ideGateway.handleIDEArguments(argCounter, argValues))
	{
		return 0;
	}

	//=============TEST=============
	if (ideGateway.doRunTest())
	{
		TestDown test;
		test.runAll();

		return 0;
	}

	//==============DOWN=============
	return runDown(ideGateway);
}

int ProgramHandler::runDown(IDEGateway& ideGateway)
{
	shared_ptr<LinkedTokenList> tokenList = nullptr;
	shared_ptr<LinkedActionList> compiledList = nullptr;

	try
	{
		//=============START-CLOCK=============
		if (ideGateway.doPrintElapsedTime())
		{
			sttime = clock();
		}

		//=============TOKENIZER=============
		tokenList = runTokenizer(ideGateway.getCode(), ideGateway.doPrintTokenList());

		if (errors())
		{
			return -1;
		}

		//=============COMPILER=============
		compiledList = runCompiler(tokenList, ideGateway.doPrintCompiledList());

		if (errors())
		{
			return -1;
		}

		//=============VM=============
		if (!ideGateway.doBuild())
		{
			runVirtualMachine(compiledList);
		}

		if (errors())
		{
			return -1;
		}

		//=============END-CLOCK=============
		if (ideGateway.doPrintElapsedTime())
		{
			printElapsedTime();
		}
	}
	catch (...)
	{
		cleanup(tokenList, compiledList);
	}
	cleanup(tokenList, compiledList);

	return 0;
}

shared_ptr<LinkedTokenList> ProgramHandler::runTokenizer(const string code, const  bool printTokenList)
{
	Tokenizer tokenizer;
	shared_ptr<LinkedTokenList> tokenList = make_shared<LinkedTokenList>();
	tokenizer.createTokenList(tokenList, code);

	if (printTokenList)
	{
		tokenizer.printTokenList(tokenList);
	}

	return tokenList;
}

shared_ptr<LinkedActionList> ProgramHandler::runCompiler(const shared_ptr<LinkedTokenList>& tokenList, const bool printCompiledList)
{
	Compute compute;
	shared_ptr<LinkedActionList> compiledList = compute.computeCompile(tokenList);

	if (printCompiledList)
	{
		compiledList->printList();
	}

	return compiledList;
}

void ProgramHandler::runVirtualMachine(const shared_ptr<LinkedActionList>& compiledList)
{
	VirtualMachine virtualMachine;
	virtualMachine.execute(compiledList);
}

void ProgramHandler::printElapsedTime()
{
	double elapsed_secs = double(clock() - sttime) / CLOCKS_PER_SEC;
	cout << "Time elapsed: " + to_string(elapsed_secs);
}

bool ProgramHandler::errors()
{
	if (!ErrorHandler::getInstance()->getErrors().empty())
	{
		cerr << ErrorHandler::getInstance()->asJson();
		printElapsedTime();

		return true;
	}

	return false;
}

void ProgramHandler::cleanup(shared_ptr<LinkedTokenList>& tokenList, shared_ptr<LinkedActionList>& compiledList)
{
	auto nextNode = compiledList->getFirst();
	compiledList.reset();

	while (nextNode)
	{
		nextNode = nextNode->getNext(); 
	}

	auto next = tokenList->getFirst();
	tokenList.reset();

	while (next)
	{
		next = next->getNext();
	}
}