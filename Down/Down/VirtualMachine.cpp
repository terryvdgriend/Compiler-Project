#include "stdafx.h"
#include "VirtualMachine.h"
#include "CommandDictionary.h"
#include "AbstractFunctionCall.h"

VirtualMachine::VirtualMachine()
{
	commandDictionary = CommandDictionary().getMap();
	runsVeryNaz = true;
}

void VirtualMachine::execute(LinkedActionList& actionList)
{
	ActionNode* currentNode = actionList.getFirst();
	shared_ptr<NodeVisitor> visitor = make_shared<NodeVisitor>(*this);

	while (currentNode != nullptr && runsVeryNaz)
	{
		AbstractFunctionCall* actionNode = dynamic_cast<AbstractFunctionCall*>(currentNode);

		if (actionNode)
		{
			string name = actionNode->getContentArrayNonConstant()[0];
			commandDictionary[name]->execute(*this, *actionNode);
			
		}
		//(*currentNode).accept(*visitor);
		//currentNode = (*visitor).nextNode;

		currentNode->accept(*visitor);
		currentNode = visitor->nextNode;
	}
}

void VirtualMachine::addIdentifer(string name)
{
	if (!isAnIdentifier(name))
	{
		identifierList.push_back(name);
	}
}

shared_ptr<Variable> VirtualMachine::getVariable(string key)
{
	map<string, shared_ptr<Variable>>::iterator it = variableDictionary.find(key);

	if (hasValueInVariableDictionary(it))
	{
		return shared_ptr<Variable>(it->second);
	}

	return nullptr;
}

void VirtualMachine::setVariable(string key, string value,Token::iToken token)
{
	map<string, shared_ptr<Variable>>::iterator it = variableDictionary.find(key);

	if (hasValueInVariableDictionary(it))
	{
		it->second = make_shared<Variable>(value);
		it->second.get()->setTokenType(token);
	}
	else
	{
		auto pair = make_pair(key, make_shared<Variable>(value));
		pair.second.get()->setTokenType(token);
		variableDictionary.insert(pair);
	}
}

list<string> VirtualMachine::getFunctionParametersByKey(string key)
{
	list<string> parameterList;
	map<string, string>::iterator it = functionParameters.begin();

	for (it; it != functionParameters.end(); it++)
	{
		if (it->second == functionParameters[key])
		{
			parameterList.push_back(it->first);
		}
	}

	return parameterList;
}

vector<string> VirtualMachine::getFunctionParametersByValue(string value)
{
	vector<string> parameterList;
	map<string, string>::iterator it = functionParameters.begin();

	for (it; it != functionParameters.end(); it++)
	{
		if (it->second == value)
		{
			parameterList.push_back(it->first);
		}
	}

	return parameterList;
}

string VirtualMachine::getFunctionParameterValueByKey(string key)
{
	string parameter;
	map<string, string>::iterator it = functionParameters.begin();

	for (it; it != functionParameters.end(); it++)
	{
		if (it->second == functionParameters[key])
		{
			parameter = it->second;
			break;
		}
	}

	return parameter;
}

vector<shared_ptr<Variable>> VirtualMachine::addArrayToDictionary(string key, int length)
{
	map<string, string>::iterator iter;
	for (iter = functionParameters.begin(); iter != functionParameters.end(); ++iter)
	{
		if (iter->first == key)
		{
			vector<shared_ptr<Variable>> temp(length);
			variableArrayDictionary.emplace(iter->first, temp);
			return temp;
		}
	}
}

vector<shared_ptr<Variable>> VirtualMachine::getVariableArray(string key)
{
	auto it = functionParameters.find(key);
	if (it != functionParameters.end()) {
		vector<shared_ptr<Variable>> varArray;
		for (auto p : functionParameters) {
			if (p.second == it->second) {
				auto it = variableArrayDictionary.find(p.first);
				if (hasValueInVariableArrayDictionary(it)) {
					varArray = it->second;
					break;
				}
				
			}
		}
		return varArray;
	}
	else {
		ErrorHandler::getInstance()->addError(Error{ "you want to get an array which doesn't exist", ".md", -1, -1, Error::error });
	}
}

void VirtualMachine::addItemToVariableArray(string key, shared_ptr<Variable> value)
{
	map<string, vector<shared_ptr<Variable>>>::iterator it = variableArrayDictionary.find(key);

	if (hasValueInVariableArrayDictionary(it))
	{
		for (int i = 0; i < it->second.size(); i++)
		{
			shared_ptr<Variable> curr = it->second.at(i);
			if (curr->getValue() == "" && curr->getType() < 0)
			{
				it->second[i] = value;
				break;
			}
		}
	}
	//else
	//{
	//	ErrorHandler::getInstance()->addError(Error{ "you want to add an item to an array which doesn't exist", ".md", -1, -1, Error::error });
	//}
}

void VirtualMachine::addItemToVariableArrayAt(string arrayKey, string key, shared_ptr<Variable> value)
{
	map<string, vector<shared_ptr<Variable>>>::iterator it = variableArrayDictionary.find(arrayKey);

	if (hasValueInVariableArrayDictionary(it))
	{
		for (int i = 0; i < it->second.size(); i++)
		{
			if (i == atoi(key.c_str()))
			{
				it->second[i] = value;
				break;
			}
		}
	}
	//else
	//{
	//	ErrorHandler::getInstance()->addError(Error{ "you want to add an item to an array which doesn't exist", ".md", -1, -1, Error::error });
	//}
}

shared_ptr<Variable> VirtualMachine::getItemFromVariableArray(string key, int index)
{
	map<string, vector<shared_ptr<Variable>>>::iterator it = variableArrayDictionary.find(key);

	if (hasValueInVariableArrayDictionary(it))
	{
		return it->second[index];
	}
	else
	{
		ErrorHandler::getInstance()->addError(Error{ "you want to get an item from an array which doesn't exist", ".md",-1, -1, Error::error });
	}
}

void VirtualMachine::addArrayTypeToArrayTypes(string arrayName, Token::iToken tokenType)
{
	VariableType type;
	switch (tokenType)
	{
		case Token::iToken::TYPE_TEXT_ARRAY:
			type = VariableType::TEXT;
			arrayType = "text";
			break;
		case Token::iToken::TYPE_NUMBER_ARRAY:
			type = VariableType::NUMBER;
			arrayType = "number";
			break;
		case Token::iToken::TYPE_FACT_ARRAY:
			type = VariableType::FACT;
			arrayType = "fact";
			break;
		default:
			break;
	}
	if (arrayTypes.find(arrayName) == arrayTypes.end())
	{
		arrayTypes.emplace(arrayName, type);
	}
}

pair<string, string> VirtualMachine::getVariableTypeSameAsArrayType(string arrayName, Token::iToken tokenType)
{
	VariableType type = VariableType::NULLTYPE;
	string tempArrayType = "";
	switch (tokenType)
	{
		case Token::iToken::TYPE_TEXT:
			type = VariableType::TEXT;
			tempArrayType = "text";
			break;
		case Token::iToken::TYPE_NUMBER:
			type = VariableType::NUMBER;
			tempArrayType = "number";
			break;
		case Token::iToken::TYPE_FACT:
			type = VariableType::FACT;
			tempArrayType = "fact";
			break;
		default:
			break;
	}
	map<string, VariableType>::iterator iter = arrayTypes.find(arrayName);
	if (iter != arrayTypes.end())
	{
		return pair<string, string>(arrayType, tempArrayType);
	}
	return pair<string, string>();
}

void VirtualMachine::setFunctionParameter(string name, string value)
{
	functionParameters[name] = value;
}

string VirtualMachine::getReturnValue()
{
	return returnValue;
}

void VirtualMachine::setReturnValue(string value)
{
	returnValue = value;
}

Token::iToken VirtualMachine::getReturnToken()
{
	return returnToken;
}

void VirtualMachine::setReturnToken(Token::iToken value)
{
	returnToken = value;
}

void VirtualMachine::triggerRunFailure()
{
	runsVeryNaz = false;
}

bool VirtualMachine::hasValueInVariableDictionary(map<string, shared_ptr<Variable>>::iterator& it)
{
	return it != variableDictionary.end();
}

bool VirtualMachine::hasValueInVariableArrayDictionary(map<string, vector<shared_ptr<Variable>>>::iterator& it)
{
	return it != variableArrayDictionary.end();
}

bool VirtualMachine::hasValueInFunctionParameters(string key)
{
	return functionParameters.find(key) != functionParameters.end();
}

bool VirtualMachine::isAnIdentifier(string name)
{
	return find(identifierList.begin(), identifierList.end(), name) != identifierList.end();
}