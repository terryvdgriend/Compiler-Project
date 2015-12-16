#pragma once
#include "LinkedActionList.h"
#include "IDEGateway.h"
#include "LinkedTokenList.h"

class ProgramHandler
{
	public:
		int runProgram(int argCounter, char* argValues[]);
				
	private:
		clock_t sttime;

		int runDown(IDEGateway& ideGateway);
		shared_ptr<LinkedTokenList> runTokenizer(const string code, const bool printTokenList);
		shared_ptr<LinkedActionList> runCompiler(const shared_ptr<LinkedTokenList>&, const bool printCompiledList);
		void runVirtualMachine(const shared_ptr<LinkedActionList>& compiledList);
		void printElapsedTime();
		bool errors();
};