#include "stdafx.h"
#include "ProgramHandler.h" 

int main(int argCounter, char* argv[])
{
	ProgramHandler programHandler;

	return programHandler.runProgram(argCounter, argv);
}