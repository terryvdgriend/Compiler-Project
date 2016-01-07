#pragma once
#include "CommandDictionary.h"
#include "LinkedActionList.h"
#include "Variable.h"
struct Array {
	vector<int> arraySizes;
	vector<shared_ptr<Variable>> variableArrayDictionary;
	Array(vector<int> sizes, vector<shared_ptr<Variable>> dictionary) {
		arraySizes = sizes;
		variableArrayDictionary = dictionary;
	}
	Array() {
		variableArrayDictionary = vector<shared_ptr<Variable>>();
	}
};

class VirtualMachine
{
	
	public:
		VirtualMachine();
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

		shared_ptr<Array> addArrayToDictionary(string key, vector<int> length);
		shared_ptr<Array> getVariableArray(string key);
		void addItemToVariableArray(string key, shared_ptr<Variable> value);
		void addItemToVariableArrayAt(string arrayKey, vector<string> key, shared_ptr<Variable> value);
		shared_ptr<Variable> getItemFromVariableArray(string key, vector<int> index);
		void addArrayTypeToArrayTypes(string arrayName, IToken tokenType);
		pair<string, string> getVariableTypeSameAsArrayType(string arrayName, IToken tokenType);	

		bool hasValueInVariableDictionary(map<string, shared_ptr<Variable>>::iterator& it);
		bool hasValueInVariableArrayDictionary(map<string, shared_ptr<Array>>::iterator& it);
		bool hasValueInFunctionParameters(string parameter);
		bool isAnIdentifier(string name);

		bool isAnArrayIdentifier(string name);

	private:
		string returnValue;
		bool errorsDetected;
		IToken returnToken;

		unique_ptr<CommandDictionary> commandDictionary;

		map<string, shared_ptr<Variable>> variableDictionary;
		map<string, string> functionParameters;
		map<string, VariableType> arrayTypes;
		map<string, shared_ptr<Array>> variableArrayDictionary;
		vector<string> identifierList;
		string arrayType;
};

