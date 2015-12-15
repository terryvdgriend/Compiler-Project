#pragma once

class IDEGateway
{
	public:
		IDEGateway();

		bool handleIDEArguments(int argCounter, char* argValues[]);

		string getCode();
		bool doPrintTokenList();
		bool doPrintCompiledList();
		bool doPrintElapsedTime();
		bool doBuild();
		bool doRunTest();

	private:
		string code;
		bool printTokenList;
		bool printCompiledList;
		bool printElapsedTime;
		bool build;
		bool runTest;
};