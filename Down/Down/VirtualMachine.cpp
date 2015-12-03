#include "stdafx.h"
#include "VirtualMachine.h"
#include "AbstractFunctionCall.h"
#include "NodeVisitor.h"
#include "Variable.h"

VirtualMachine::VirtualMachine()
{
	commandDictionary	= make_unique<CommandDictionary>();
	errorsDetected		= false;
}

void VirtualMachine::execute(LinkedActionList& actionList)
{
	unique_ptr<NodeVisitor> visitor = make_unique<NodeVisitor>(*this);
	map<string, shared_ptr<BaseCommand>> map = commandDictionary->getMap();
	shared_ptr<ActionNode> currentNode = actionList.getFirst();

    while (currentNode != nullptr && !errorsDetected)
	{
		AbstractFunctionCall* actionNode = dynamic_cast<AbstractFunctionCall*>(currentNode.get());

		if (actionNode != nullptr)
		{
			string name = actionNode->getContentArrayNonConstant()[0];
			map[name]->execute(*this, actionNode->getContentArrayNonConstant());
			
		}
		currentNode->accept(*visitor);
		currentNode = visitor->getNextNode();
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
	errorsDetected = true;
}

bool VirtualMachine::hasValueInVariableDictionary(map<string, shared_ptr<Variable>>::iterator& it)
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