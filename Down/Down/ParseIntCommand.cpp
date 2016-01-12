#include "stdafx.h"
#include "ParseIntCommand.h"
#include "MandatoryCommandIncludes.h"

ParseIntCommand::ParseIntCommand()
{
}


ParseIntCommand::~ParseIntCommand()
{
}

void ParseIntCommand::execute(VirtualMachine & vm, AbstractFunctionCall & node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();
	auto var = vm.getVariable(parameters.at(1));

	if (var->getType() != VariableType::nulltype) {
		if (var->getTokenType() == IToken::TYPE_TEXT) {
			string val = var->getValue();
			val.erase(remove(val.begin(), val.end(), '\"'), val.end());
			if (is_number(val)) {
				vm.setReturnToken(TYPE_NUMBER);
				vm.setReturnValue(val);
			}
			else {
				throwCustomError("given value was not a numeric value.", vm, node.getToken());
			}
		}
		else {
			throwCustomError("given value was not a string.", vm, node.getToken());
		}
	}
	else {
		throwCustomError("given value was not set.", vm, node.getToken());
	}
}

bool ParseIntCommand::is_number(const string& s)
{
	string::const_iterator it = s.begin();
	bool decimalPoint = false;
	int minSize = 0;

	if (s.size()>0 && (s[0] == '-' || s[0] == '+'))
	{
		it++;
		minSize++;
	}

	while (it != s.end())
	{
		if (*it == '.')
		{
			if (!decimalPoint)
			{
				decimalPoint = true;
			}
			else
			{
				break;
			}
		}
		else if (!isdigit(*it) && ((*it != 'f') || it + 1 != s.end() || !decimalPoint))
		{
			break;
		}
		++it;
	}

	return s.size() > (size_t)minSize && it == s.end();
}

pair<string, string> ParseIntCommand::accept(CommandVisitor & cmdVisitor)
{
	return cmdVisitor.visit(*this);
}
