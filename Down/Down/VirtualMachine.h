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

		list<string> getFunctionParametersByKey(string name);
		vector<string> getFunctionParametersByValue(string value);
		string getFunctionParameterValueByKey(string key);
		void setFunctionParameter(string name, string value);

		void addIdentifer(string name);

		vector<shared_ptr<Variable>> addArrayToDictionary(string key, int length);
		vector<shared_ptr<Variable>> getVariableArray(string key);
		void addItemToVariableArray(string key, shared_ptr<Variable> value);
		void addItemToVariableArrayAt(string arrayKey, string key, shared_ptr<Variable> value);
		shared_ptr<Variable> getItemFromVariableArray(string key, int index);
		void addArrayTypeToArrayTypes(string arrayName, IToken tokenType);
		pair<string, string> VirtualMachine::getVariableTypeSameAsArrayType(string arrayName, IToken tokenType);	

		bool hasValueInVariableDictionary(map<string, shared_ptr<Variable>>::iterator& it);
		bool hasValueInVariableArrayDictionary(map<string, vector<shared_ptr<Variable>>>::iterator& it);
		bool hasValueInFunctionParameters(string parameter);
		bool isAnIdentifier(string name);
		
	private:
		string returnValue;
		bool errorsDetected;
		IToken returnToken;

		unique_ptr<CommandDictionary> commandDictionary;
		shared_ptr<NodeVisitor> nodeVisitor;

		map<string, shared_ptr<Variable>> variableDictionary;
		map<string, string> functionParameters;
		map<string, VariableType> arrayTypes;
		map<string, vector<shared_ptr<Variable>>> variableArrayDictionary;

		vector<string> identifierList;
		string arrayType;
};