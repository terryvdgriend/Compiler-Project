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
	unique_ptr<NodeVisitor> visitor = make_unique<NodeVisitor>(*this);

	while (currentNode != nullptr && runsVeryNaz)
	{
		AbstractFunctionCall* actionNode = dynamic_cast<AbstractFunctionCall*>(currentNode);

		if (actionNode)
		{
			string name = actionNode->getContentArrayNonConstant()[0];
			commandDictionary[name]->execute(*this, actionNode->getContentArrayNonConstant());
			
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

void VirtualMachine::setVariable(string key, string value)
{
	map<string, shared_ptr<Variable>>::iterator it = variableDictionary.find(key);

	if (hasValueInVariableDictionary(it))
	{
		it->second = make_shared<Variable>(value);
	}
	else
	{
		variableDictionary.insert(make_pair(key, make_shared<Variable>(value)));
	}
}

vector<string> VirtualMachine::getFunctionParametersByKey(string key)
{
	vector<string> parameterList;
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

vector<Variable> VirtualMachine::addArrayToDictionary(string key, int length)
{
	map<string, string>::iterator iter;
	for (iter = functionParameters.begin(); iter != functionParameters.end(); ++iter)
	{
		if (iter->first == key)
		{
			vector<Variable> temp(length);
			variableArrayDictionary.emplace(iter->first, temp);
			return temp;
		}
	}
}

vector<Variable> VirtualMachine::getVariableArray(string key)
{
	map<string, vector<Variable>>::iterator it = variableArrayDictionary.find(key);

	if (hasValueInVariableArrayDictionary(it))
	{
		return it->second;
	}
	else
	{
		ErrorHandler::getInstance()->addError(Error{ "you want to get an array which doesn't exist", ".md", -1, -1, Error::error });
	}
}

void VirtualMachine::addItemToVariableArray(string key, Variable value)
{
	map<string, vector<Variable>>::iterator it = variableArrayDictionary.find(key);

	if (hasValueInVariableArrayDictionary(it))
	{
		for (int i = 0; i < it->second.size(); i++)
		{
			Variable curr = it->second.at(i);
			if (curr.getValue() == "" && curr.getType() < 0)
			{
				it->second[i] = value;
				break;
			}
		}
	}
	else
	{
		ErrorHandler::getInstance()->addError(Error{ "you want to add an item to an array which doesn't exist", ".md", -1, -1, Error::error });
	}
}

void VirtualMachine::addItemToVariableArrayAt(string arrayKey, string key, Variable value)
{
	map<string, vector<Variable>>::iterator it = variableArrayDictionary.find(arrayKey);

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
	else
	{
		ErrorHandler::getInstance()->addError(Error{ "you want to add an item to an array which doesn't exist", ".md", -1, -1, Error::error });
	}
}

Variable VirtualMachine::getItemFromVariableArray(string key, int index)
{
	map<string, vector<Variable>>::iterator it = variableArrayDictionary.find(key);

	if (hasValueInVariableArrayDictionary(it))
	{
		return it->second[index];
	}
	else
	{
		ErrorHandler::getInstance()->addError(Error{ "you want to get an item from an array which doesn't exist", ".md",-1, -1, Error::error });
	}
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

void VirtualMachine::triggerRunFailure()
{
	runsVeryNaz = false;
}

bool VirtualMachine::hasValueInVariableDictionary(map<string, shared_ptr<Variable>>::iterator& it)
{
	return it != variableDictionary.end();
}

bool VirtualMachine::hasValueInVariableArrayDictionary(map<string, vector<Variable>>::iterator& it)
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