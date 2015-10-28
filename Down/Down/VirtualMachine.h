#pragma once
#include "LinkedList.h"
#include "Variable.h"

using namespace std;

class BaseCommand;

class VirtualMachine
{
	public:
		VirtualMachine();

		void execute(LinkedList linkedList);

		BaseCommand* getCommandByString(string name);

		Variable getVariable(string parameter);
		void setVariable(string name, string value);

		bool hasValueInFunctionParameters(string parameter);
		vector<string> getFunctionParamters(string name);
		vector<string> getFunctionParametersByValue(string value);
		void setFunctionParamter(string name, string value);

		void addIdentifer(string name);
		bool isAnIdentifier(string name);

		string getReturnValue();
		void setReturnValue(string value);

	private:
		string returnValue;

		map<string, BaseCommand*> commandDictionary;
		map<string, Variable> variableDictionary;
		map<string, string> functionParamters;

		vector<string> identifierList;
};