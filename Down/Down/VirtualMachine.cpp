#pragma once
#include "stdafx.h"
#include "VirtualMachine.h"
#include "CommandDictionary.h"

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
	return nullptr;
}

Variable VirtualMachine::getVariable(string parameter)
{
	return Variable();
}

void VirtualMachine::setVariable(string name, string value)
{
}

bool VirtualMachine::hasValueInFunctionParameters(string parameter)
{
	return false;
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
}

void VirtualMachine::addIdentifer(string name)
{
}

bool VirtualMachine::isAnIdentifier(string name)
{
	return false;
}
