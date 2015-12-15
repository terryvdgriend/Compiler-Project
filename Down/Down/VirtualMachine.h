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

		shared_ptr<Variable> getVariable(string parameter);
		void setVariable(string key, string value, Token::iToken token);
		vector<shared_ptr<Variable>> addArrayToDictionary(string key, int length);
		vector<shared_ptr<Variable>> getVariableArray(string key);
		void addItemToVariableArray(string key, shared_ptr<Variable> value);
		void addItemToVariableArrayAt(string arrayKey, string key, shared_ptr<Variable> value);
		shared_ptr<Variable> getItemFromVariableArray(string key, int index);
		list<string> getFunctionParametersByKey(string name);
		vector<string> getFunctionParametersByValue(string value);
		string getFunctionParameterValueByKey(string key);
		void setFunctionParameter(string name, string value);
		string getReturnValue();
		void setReturnValue(string value);

		Token::iToken getReturnToken();
		void setReturnToken(Token::iToken value);

		void triggerRunFailure();

		bool hasValueInVariableDictionary(map<string, shared_ptr<Variable>>::iterator& it);
		bool hasValueInVariableArrayDictionary(map<string, vector<shared_ptr<Variable>>>::iterator& it);

		bool hasValueInFunctionParameters(string parameter);
		bool isAnIdentifier(string name);

		void addArrayTypeToArrayTypes(string arrayName, Token::iToken tokenType);
		pair<string, string> VirtualMachine::getVariableTypeSameAsArrayType(string arrayName, Token::iToken tokenType);
		
	private:
		string returnValue;
		bool runsVeryNaz;
		Token::iToken returnToken;

		map<string, shared_ptr<BaseCommand>> commandDictionary;
		map<string, shared_ptr<Variable>> variableDictionary;
		map<string, string> functionParameters;

		map<string, VariableType> arrayTypes;

		map<string, vector<shared_ptr<Variable>>> variableArrayDictionary;

		vector<string> identifierList;

		string arrayType;
};