#include "stdafx.h"
#include "VirtualMachine.h"
#include "AbstractFunctionCall.h"
#include "NodeVisitor.h"
#include "Variable.h"

VirtualMachine::VirtualMachine()
{
	commandDictionary	= make_unique<CommandDictionary>();
	errorsDetected = false;
}

void VirtualMachine::init(shared_ptr<VirtualMachine>& vm)
{
	nodeVisitor = make_shared<NodeVisitor>(vm);
}

void VirtualMachine::execute(const shared_ptr<LinkedActionList>& actionList)
{
	map<string, shared_ptr<BaseCommand>> map = commandDictionary->getMap();
	shared_ptr<ActionNode> currentNode = actionList->getFirst();

    while (currentNode != nullptr && !errorsDetected)
	{
		AbstractFunctionCall* actionNode = dynamic_cast<AbstractFunctionCall*>(currentNode.get());

		if (actionNode != nullptr)
		{
			string name = actionNode->getContentArrayNonConstant()[0];
			map[name]->execute(*this, *actionNode);	
		}
		currentNode->accept(nodeVisitor);
		currentNode = nodeVisitor->getNextNode();
	}
}

void VirtualMachine::triggerRunFailure()
{
	errorsDetected = true;
}

string VirtualMachine::getReturnValue()
{
	return returnValue;
}

void VirtualMachine::setReturnValue(string value)
{
	returnValue = value;
}

IToken VirtualMachine::getReturnToken()
{
	return returnToken;
}

void VirtualMachine::setReturnToken(IToken value)
{
	returnToken = value;
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

void VirtualMachine::setVariable(string key, string value, IToken token)
{
	map<string, shared_ptr<Variable>>::iterator it = variableDictionary.find(key);

	if (hasValueInVariableDictionary(it))
	{
		it->second = make_shared<Variable>(value);
		it->second.get()->setTokenType(token);
	}
	else
	{
		pair<string, shared_ptr<Variable>> pair = make_pair(key, make_shared<Variable>(value));
		pair.second.get()->setTokenType(token);
		variableDictionary.insert(pair);
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

void VirtualMachine::addIdentifer(string name)
{
	if (!isAnIdentifier(name))
	{
		identifierList.push_back(name);
	}
}

bool VirtualMachine::hasValueInVariableDictionary(map<string, shared_ptr<Variable>>::iterator& it)
{
	return it != variableDictionary.end();
}

bool VirtualMachine::isAnIdentifier(string name)
{
	return find(identifierList.begin(), identifierList.end(), name) != identifierList.end();
}

bool VirtualMachine::hasValueInFunctionParameters(string key)
{
	return functionParamters.find(key) != functionParamters.end();
}