#include "stdafx.h"
#include "VirtualMachine.h"
#include "CommandDictionary.h"


VirtualMachine::VirtualMachine()
{
	commandDictionary = CommandDictionary().getMap();
}

void VirtualMachine::execute(LinkedActionList& actionList)
{
	//ActionNode* currentNode = actionList.getFirst();
	//NodeVisitor* visitor = new NodeVisitor(*this);

	//while (currentNode != nullptr)
	//{
	//	AbstractFunctionCall* actionNode = dynamic_cast<AbstractFunctionCall*>(currentNode);

	//	if (actionNode != nullptr)
	//	{
	//		//string name = (*actionNode).get
	//	}
	//}
}

void VirtualMachine::addIdentifer(string name)
{
	if (!isAnIdentifier(name))
	{
		identifierList.push_back(name);
	}
}

BaseCommand* VirtualMachine::getCommandByString(string key)
{
	return commandDictionary[key];
}

Variable* VirtualMachine::getVariable(string key)
{
	map<string, Variable>::iterator it = variableDictionary.find(key);

	if (hasValueInVariableDictionary(it))
	{
		return &it->second;
	}

	return nullptr;
}

void VirtualMachine::setVariable(string key, string value)
{
	map<string, Variable>::iterator it = variableDictionary.find(key);

	if (!hasValueInVariableDictionary(it))
	{
		it->second = value;
	}
	else
	{
		variableDictionary.insert(make_pair(key, value));
	}
}

vector<string> VirtualMachine::getFunctionParametersByKey(string key)
{
	vector<string> parameterList;
	map<string, string>::iterator it = functionParamters.begin();

	for (it; it != functionParamters.end(); it++)
	{
		if (it->second == functionParamters[key])
		{
			parameterList.push_back(it->first);
		}
	}

	return parameterList;
}

vector<string> VirtualMachine::getFunctionParametersByValue(string value)
{
	vector<string> parameterList;
	map<string, string>::iterator it = functionParamters.begin();

	for (it; it != functionParamters.end(); it++)
	{
		if (it->second == value)
		{
			parameterList.push_back(it->first);
		}
	}

	return parameterList;
}

void VirtualMachine::setFunctionParameter(string name, string value)
{
	functionParamters[name] = value;
}

string VirtualMachine::getReturnValue()
{
	return returnValue;
}

void VirtualMachine::setReturnValue(string value)
{
	returnValue = value;
}

bool VirtualMachine::hasValueInVariableDictionary(map<string, Variable>::iterator& it)
{
	return it != variableDictionary.end();
}

bool VirtualMachine::hasValueInFunctionParameters(string key)
{
	return functionParamters.find(key) != functionParamters.end();
}

bool VirtualMachine::isAnIdentifier(string name)
{
	return find(identifierList.begin(), identifierList.end(), name) != identifierList.end();
}