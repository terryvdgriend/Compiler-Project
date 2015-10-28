#pragma once
#include "stdafx.h"
#include "VirtualMachine.h"
#include "CommandDictionary.h"
#include <algorithm>

VirtualMachine::VirtualMachine()
{
	commandDictionary = CommandDictionary().getMap();
}

VirtualMachine::~VirtualMachine()
{
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
	Variable temp;
	temp = variableDictionary.find(parameter)->second;

	return temp;
}

void VirtualMachine::setVariable(string name, string value)
{

}

bool VirtualMachine::hasValueInFunctionParameters(string parameter)
{
	return functionParamters.find(parameter) != functionParamters.end();
}

vector<string> VirtualMachine::getFunctionParamters(string name)
{
	return vector<string>();
}

vector<string> VirtualMachine::getFunctionParametersByValue(string value)
{
	return vector<string>();
}

void VirtualMachine::setFunctionParamter(string name, string value)
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