#pragma once

class ConstantToReturnValueCommand;
class DivideCommand;
class EqualsCommand;
class EqualsToCommand;
class GetFromValueCommand;
class GreaterEqualsToCommand;
class GreaterThanCommand;
class IdentifierToReturnValueCommand;
class MinusCommand;
class MinusMinusCommand;
class ModuloCommand;
class NotEqualsToCommand;
class PlusCommand;
class PlusPlusCommand;
class SmallerEqualsToCommand;
class SmallerThanCommand;
class TimesCommand;

// Library functions
class ShowFunctionCommand;

class CommandVisitor 
{
	public: 
		pair<string, string> visit(ConstantToReturnValueCommand& command);
		pair<string, string> visit(DivideCommand& command);
		pair<string, string> visit(EqualsCommand& command);
		pair<string, string> visit(EqualsToCommand& command);
		pair<string, string> visit(GetFromValueCommand& command);
		pair<string, string> visit(GreaterEqualsToCommand& command);
		pair<string, string> visit(GreaterThanCommand& command);
		pair<string, string> visit(IdentifierToReturnValueCommand& command);
		pair<string, string> visit(MinusCommand& command);
		pair<string, string> visit(MinusMinusCommand& command);
		pair<string, string> visit(ModuloCommand& command);
		pair<string, string> visit(NotEqualsToCommand& command);
		pair<string, string> visit(PlusCommand& command);
		pair<string, string> visit(PlusPlusCommand& command);
		pair<string, string> visit(SmallerEqualsToCommand& command);
		pair<string, string> visit(SmallerThanCommand& command);
		pair<string, string> visit(TimesCommand& command);

		// Library functions
		pair<string, string> visit(ShowFunctionCommand& command);
};