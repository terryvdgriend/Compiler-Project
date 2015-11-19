#pragma once
#include "LinkedActionList.h"
#include "Variable.h"

class BaseCommand;

class VirtualMachine
{
	public:
		VirtualMachine();

		void execute(LinkedActionList& actionList);

		void addIdentifer(string name);

		BaseCommand* getCommandByString(string name);
		Variable* getVariable(string parameter);
		void setVariable(string name, string value);
		vector<Variable> addArrayToDictionary(string key, int length);
		vector<Variable> getVariableArray(string key);
		void addItemToVariableArray(string key, Variable value);
		Variable getItemFromVariableArray(string key, int index);
		vector<string> getFunctionParametersByKey(string name);
		vector<string> getFunctionParametersByValue(string value);
		string getFunctionParameterValueByKey(string key);
		void setFunctionParameter(string name, string value);
		string getReturnValue();
		void setReturnValue(string value);
		void triggerRunFailure();

		bool hasValueInVariableDictionary(map<string, Variable>::iterator& it);
		bool hasValueInVariableArrayDictionary(map<string, vector<Variable>>::iterator& it);
		bool hasValueInFunctionParameters(string parameter);
		bool isAnIdentifier(string name);
		
	private:
		string returnValue;
		bool runsVeryNaz;

		map<string, BaseCommand*> commandDictionary;
		map<string, Variable> variableDictionary;
		map<string, string> functionParameters;

		map<string, vector<Variable>> variableArrayDictionary;

		vector<string> identifierList;
};