#include "stdafx.h"
#include "ShowFunctionCommand.h"
#include <iostream>
#include <algorithm>
#include "CommandVisitor.h"

void ShowFunctionCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();

	Variable variable2 = *vm.getVariable(parameters.at(1));
	string val = "";

	if (variable2.getType() != VariableType::NULLTYPE) {
		val += variable2.getValue();
	}

	val.erase(remove(val.begin(), val.end(), '\"'), val.end());
	cout << val << endl;
}

pair<string, string> ShowFunctionCommand::accept(CommandVisitor & cmdVisitor)
{
	return pair<string, string>();
}


void ShowUpFunctionCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();

	Variable variable2 = *vm.getVariable(parameters.at(1));
	string val = "";

	if (variable2.getType() != VariableType::NULLTYPE) {
		val += variable2.getValue();
	}

	val.erase(remove(val.begin(), val.end(), '\"'), val.end());
	cout << "UP: " + val << endl;
}
pair<string, string> ShowUpFunctionCommand::accept(CommandVisitor & cmdVisitor){	return pair<string, string>();}


void RandomFunctionCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();

	Variable variable2 = *vm.getVariable(parameters.at(1));
	string val = "";

	if (variable2.getType() != VariableType::NULLTYPE) {
		val += variable2.getValue();
	}

	val.erase(remove(val.begin(), val.end(), '\"'), val.end());
	vm.setReturnValue("666");
//	cout << "para1: " + val << " para2: " + val  << " random:" << returnValue << endl;
}
pair<string, string> RandomFunctionCommand::accept(CommandVisitor & cmdVisitor) { return pair<string, string>(); }
