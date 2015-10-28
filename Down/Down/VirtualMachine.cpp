#pragma once
#include "stdafx.h"
#include "VirtualMachine.h"
#include "CommandDictionary.h"
#include "ActionNode.h"

VirtualMachine::VirtualMachine()
{
	commandDictionary = CommandDictionary().getMap();
}

void VirtualMachine::execute(LinkedList linkedList)
{
		
}

BaseCommand * VirtualMachine::getCommandByString(string name)
{
	return commandDictionary[name];
}

Variable VirtualMachine::getVariable(string parameter)
{
	return variableDictionary[parameter];
}

void VirtualMachine::setVariable(string name, string value)
{
	variableDictionary[name] = Variable(value);
}

bool VirtualMachine::hasValueInFunctionParameters(string parameter)
{
	return functionParamters.find(parameter) != functionParamters.end();
}

vector<string> VirtualMachine::getFunctionParameters(string name)
{
	return vector<string>();
}

vector<string> VirtualMachine::getFunctionParametersByValue(string value)
{
	return vector<string>();
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

bool VirtualMachine::isAnIdentifier(string name)
{
	return find(identifierList.begin(), identifierList.end(), name) != identifierList.end();
}

string VirtualMachine::getReturnValue()
{
	return returnValue;
}

void VirtualMachine::setReturnValue(string value)
{
	returnValue = value;
}