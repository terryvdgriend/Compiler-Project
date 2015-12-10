#include "stdafx.h"
#include "ProgramHandler.h" 

int main(int argCounter, char* argv[])
{
	ProgramHandler* programHandler = new ProgramHandler();
	int result = programHandler->runProgram(argCounter, argv);

	delete programHandler;

	return result;
}