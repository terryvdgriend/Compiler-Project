#include "stdafx.h"
#include "ProgramHandler.h" 

int main(int argCounter, char* argValues[])
{
	ProgramHandler programHandler;

	return programHandler.runProgram(argCounter, argValues);
}