#include "stdafx.h"
#include "GetFromValueCommand.h"
#include <vector>

void GetFromValueCommand::execute(VirtualMachine& vm, vector<string>& parameters)
{
	string rValue = vm.getReturnValue();

	if (&rValue != nullptr) { // TODO: test

		if (vm.isAnIdentifier(rValue)) {

			if (vm.hasValueInFunctionParameters(parameters[1])) {
				
				vector<string> value = vm.getFunctionParametersByValue(rValue);
				
				if (value.size() > 0) {

					vm.setVariable(parameters[1], value.back());
				}
				else {
					vm.setVariable(parameters[1], nullptr);
				}

				vm.setFunctionParameter(parameters[1], rValue);
			}

			vm.setReturnValue(nullptr);
		}
		else {
			vm.setVariable(parameters[1], rValue);
		}
	}
}