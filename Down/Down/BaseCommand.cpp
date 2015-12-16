#include "stdafx.h"
#include "BaseCommand.h"
#include "MandatoryCommandIncludes.h"

bool BaseCommand::isUndefined(Variable& var1, Variable& var2, VirtualMachine& vm) 
{
	if (var1.getType() == VariableType::nulltype || var2.getType() == VariableType::nulltype)
	{
		CommandVisitor cmdVisitor;
		pair<string, string> words = accept(cmdVisitor);

		if (var1.getType() == VariableType::nulltype && var2.getType() == VariableType::nulltype)
		{
            auto error = make_shared<Error>("cannot " + words.first + " undefined " + words.second + " undefined", ".md", -1, -1, ErrorType::ERROR);
			ErrorHandler::getInstance()->addError(error);
			vm.triggerRunFailure();

			return true;
		}
		else if (var1.getType() == VariableType::nulltype)
		{
            auto error = make_shared<Error>("cannot " + words.first + " undefined " + words.second + " " + var2.getValue(), ".md", -1, -1, ErrorType::ERROR);
			ErrorHandler::getInstance()->addError(error);
			vm.triggerRunFailure();

			return true;
		}
		else if (var2.getType() == VariableType::nulltype)
		{
            auto error = make_shared<Error>("cannot " + words.first + " " + var1.getValue() + " " + words.second + " undefined", ".md", -1, -1, ErrorType::ERROR);
			ErrorHandler::getInstance()->addError(error);
			vm.triggerRunFailure();

			return true;
		}
	}

	return false;
}

void BaseCommand::throwTypeError(Variable& var1, Variable& var2, VirtualMachine& vm) 
{
	CommandVisitor cmdVisitor;
	pair<string, string> words = accept(cmdVisitor);

    auto error = make_shared<Error>("cannot " + words.first + " " + var1.getValue() + " " + words.second + " " + var2.getValue(), ".md", -1, -1, ErrorType::ERROR);
	ErrorHandler::getInstance()->addError(error);
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

void BaseCommand::throwCustomError(string error, VirtualMachine& vm)
{
    auto err = make_shared<Error>(error, ".md", -1, -1, ErrorType::ERROR);
	ErrorHandler::getInstance()->addError(err);
	vm.triggerRunFailure();
}
