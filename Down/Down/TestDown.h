#pragma once
#include "LinkedActionList.h"
#include "LinkedTokenList.h"

class TestDown
{
	public:
		void runAll();
		void run(string _name, string _code);
		void run(string _name, string _code, list<string> _expectedErrors);

	private:
		list<Error> expectedErrors;
		void errors(string _name, list<string> expectedErrors);

		void cleanup(shared_ptr<LinkedTokenList>& tokenList, shared_ptr<LinkedActionList>& compiledList);
};