#include "stdafx.h"
#include "ProgramHandler.h" 
#include <vld.h> 

int main(int argCounter, char* argValues[])
{
	ProgramHandler programHandler;
	int result = programHandler.runProgram(argCounter, argValues);

	return result;
}