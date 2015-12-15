#include "stdafx.h"

#include "BaseCommand.h"
#include "CommandVisitor.h"

bool BaseCommand::isUndefined(Variable& var1, Variable& var2, VirtualMachine& vm) {

	if (var1.getType() == VariableType::NULLTYPE || var2.getType() == VariableType::NULLTYPE) {

		CommandVisitor cmdVisitor;
		pair<string, string> words = accept(cmdVisitor);

		if (var1.getType() == VariableType::NULLTYPE && var2.getType() == VariableType::NULLTYPE) {
			ErrorHandler::getInstance()->addError(Error{ "cannot " + words.first + " undefined " + words.second + " undefined", ".md", -1, -1, Error::error });
			vm.triggerRunFailure();
			return true;
		}
		else if (var1.getType() == VariableType::NULLTYPE) {
			ErrorHandler::getInstance()->addError(Error{ "cannot " + words.first + " undefined " + words.second + " " + var2.getValue(),".md", -1, -1, Error::error });
			vm.triggerRunFailure();
			return true;
		}
		else if (var2.getType() == VariableType::NULLTYPE) {
			ErrorHandler::getInstance()->addError(Error{ "cannot " + words.first + " " + var1.getValue() + " " + words.second + " undefined",".md", -1, -1, Error::error });
			vm.triggerRunFailure();
			return true;
		}
	}

	return false;
}

void BaseCommand::throwTypeError(Variable& var1, Variable& var2, VirtualMachine& vm) {

	CommandVisitor cmdVisitor;
	pair<string, string> words = accept(cmdVisitor);

	ErrorHandler::getInstance()->addError(Error{ "cannot " + words.first + " " + var1.getValue() + " " + words.second + " " + var2.getValue(),".md", -1, -1, Error::error });
	vm.triggerRunFailure();
}

string BaseCommand::removeUnnecessaryDotsAndZeros(string input) {

	if (input.find('.') != std::string::npos) {

		while (input.size() != 0) {
			char current = input[input.size() - 1];

			if (current == '0') {
				input = input.substr(0, input.size() - 1);
			}
			else {
				if (current == '.') {
					input = input.substr(0, input.size() - 1);
				}
				break;
			}
		}
	}
	return input;
}
