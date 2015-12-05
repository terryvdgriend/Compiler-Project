#pragma once
#include "CommandDictionary.h"
#include "LinkedActionList.h"
#include "Variable.h"

class VirtualMachine
{
	public:
		VirtualMachine();
		
		void init(shared_ptr<VirtualMachine>& vm);
		void execute(const shared_ptr<LinkedActionList>& actionList);

		void addIdentifer(string name);

		shared_ptr<Variable> getVariable(string parameter);
		void setVariable(string name, string value);
		vector<string> getFunctionParametersByKey(string name);
		vector<string> getFunctionParametersByValue(string value);
		void setFunctionParameter(string name, string value);
		string getReturnValue();
		void setReturnValue(string value);
		void triggerRunFailure();

		bool hasValueInFunctionParameters(string parameter);
		bool isAnIdentifier(string name);
		
	private:
		string returnValue;
		bool errorsDetected;

		unique_ptr<CommandDictionary> commandDictionary;
		shared_ptr<NodeVisitor> nodeVisitor;

		map<string, shared_ptr<Variable>> variableDictionary;
		map<string, string> functionParamters;
		vector<string> identifierList;

		bool hasValueInVariableDictionary(map<string, shared_ptr<Variable>>::iterator& it);
};