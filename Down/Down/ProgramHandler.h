#pragma once
#include "LinkedActionList.h"
#include "LinkedTokenList.h"

class ProgramHandler
{
	public:
		int runProgram(int argCounter, char* argv[]);
				
	private:
		clock_t sttime;

		bool executeTest();
		int runDown(const string code, const bool printTokenList, const bool printCompiledList, const bool build);
		shared_ptr<LinkedTokenList> runTokenizer(const string code, const bool printTokenList);
		shared_ptr<LinkedActionList> runCompiler(const shared_ptr<LinkedTokenList>&, const bool printCompiledList);
		void runVirtualMachine(const shared_ptr<LinkedActionList>& compiledList);
		void printElapsedTime();
		bool errors();
};