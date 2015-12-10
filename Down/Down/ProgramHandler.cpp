#include "stdafx.h"
#include "ProgramHandler.h"
#include "Compute.h"
#include "IDEGateway.h"
#include "Tokenizer.h"
#include "VirtualMachine.h"

int ProgramHandler::runProgram(int argCounter, char* argv[])
{
	IDEGateway ideGateway;

	//==============IDE==============
	if (!ideGateway.handleIDEArguments(argCounter, argv))
	{
		return 0;
	}

	//=============CLOCK=============
	if (ideGateway.doPrintElapsedTime())
	{
		sttime = clock();
	}

	//=============TEST==============
	if (ideGateway.doRunTest())
	{
		if (!executeTest())
		{
			return -1;
		}
	}

	//==============DOWN=============
	return runDown(ideGateway.getCode(), ideGateway.doPrintTokenList(), ideGateway.doPrintCompiledList(), ideGateway.doBuild());
}

bool ProgramHandler::executeTest()
{
	//(1) Run test
	//(2) Return errors... That's it
	cerr << "========== Test runned with x amount of errors ============";

	return errors();
}

int ProgramHandler::runDown(const string code, const bool printTokenList, const bool printCompiledList, const bool build)
{
	//==============TOKENIZER========
	shared_ptr<LinkedTokenList> tokenList = runTokenizer(code, printTokenList);

	if (errors())
	{
		return -1;
	}

	//==============COMPILER=========
	shared_ptr<LinkedActionList> compiledList = runCompiler(tokenList, printCompiledList);

	if (errors())
	{
		return -1;
	}

	if (!build)
	{
		//==============VM===============
		runVirtualMachine(compiledList);
	}

	if (errors())
	{
		return -1;
	}

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
	shared_ptr<VirtualMachine> virtualMachine = make_shared<VirtualMachine>();
	virtualMachine->init(virtualMachine);
	virtualMachine->execute(compiledList);
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