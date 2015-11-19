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