#pragma once
#include "stdafx.h"
#include "ShowFunctionCommand.h"
#include <iostream>
#include <algorithm>

void ShowFunctionCommand::execute(VirtualMachine& vm, vector<string>& parameters)
{
	Variable variable2 = vm.getVariable(parameters.at(2));
	string val = "";

	string * valpointer = &variable2.getValue();

	if (valpointer != nullptr) {
		val += variable2.getValue();
	}

	val.erase(remove(val.begin(), val.end(), '\"'), val.end());
	cout << val << endl;
}