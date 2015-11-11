#include "stdafx.h"
#include "VirtualMachine.h"
#include "CommandDictionary.h"
#include "AbstractFunctionCall.h"

VirtualMachine::VirtualMachine()
{
	int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	flag |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(flag);

	commandDictionary = CommandDictionary().getMap();
	runsVeryNaz = true;
}

void VirtualMachine::execute(LinkedActionList& actionList)
{
	ActionNode* currentNode = actionList.getFirst();
	NodeVisitor* visitor = new NodeVisitor(*this);

	while (currentNode != nullptr && runsVeryNaz)
	{
		
		AbstractFunctionCall* actionNode = dynamic_cast<AbstractFunctionCall*>(currentNode);
		if (actionNode)
		{
			string name = actionNode->getContentArrayNonConstant()[0];
			commandDictionary[name]->execute(*this, actionNode->getContentArrayNonConstant());
		}
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

shared_ptr<BaseCommand> VirtualMachine::getCommandByString(string key)
{
	return shared_ptr<BaseCommand>(commandDictionary[key]);
}

shared_ptr<Variable> VirtualMachine::getVariable(string key)
{
	map<string, Variable>::iterator it = variableDictionary.find(key);

	if (hasValueInVariableDictionary(it))
	{
		return shared_ptr<Variable>(&it->second);
	}

	return nullptr;
}

void VirtualMachine::setVariable(string key, string value)
{
	map<string, Variable>::iterator it = variableDictionary.find(key);

	if (hasValueInVariableDictionary(it))
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

void VirtualMachine::triggerRunFailure()
{
	runsVeryNaz = false;
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