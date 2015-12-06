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
		void triggerRunFailure();
		
		string getReturnValue();
		void setReturnValue(string value);
		IToken getReturnToken();
		void setReturnToken(IToken value);

		shared_ptr<Variable> getVariable(string parameter);
		void setVariable(string key, string value, IToken token);
		vector<string> getFunctionParametersByKey(string name);
		vector<string> getFunctionParametersByValue(string value);
		void setFunctionParameter(string name, string value);
		void addIdentifer(string name);

		bool hasValueInFunctionParameters(string parameter);
		bool isAnIdentifier(string name);
		
	private:
		string returnValue;
		bool errorsDetected;
		IToken returnToken;

		unique_ptr<CommandDictionary> commandDictionary;
		shared_ptr<NodeVisitor> nodeVisitor;

		map<string, shared_ptr<Variable>> variableDictionary;
		map<string, string> functionParamters;
		vector<string> identifierList;

		bool hasValueInVariableDictionary(map<string, shared_ptr<Variable>>::iterator& it);
};