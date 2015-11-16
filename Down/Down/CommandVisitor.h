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
class ShowFunctionCommand;
class SmallerEqualsToCommand;
class SmallerThanCommand;
class TimesCommand;

class CommandVisitor {
public: 
	std::pair<string, string> visit(ConstantToReturnValueCommand& command);
	std::pair<string, string> visit(DivideCommand& command);
	std::pair<string, string> visit(EqualsCommand& command);
	std::pair<string, string> visit(EqualsToCommand& command);
	std::pair<string, string> visit(GetFromValueCommand& command);
	std::pair<string, string> visit(GreaterEqualsToCommand& command);
	std::pair<string, string> visit(GreaterThanCommand& command);
	std::pair<string, string> visit(IdentifierToReturnValueCommand& command);
	std::pair<string, string> visit(MinusCommand& command);
	std::pair<string, string> visit(MinusMinusCommand& command);
	std::pair<string, string> visit(ModuloCommand& command);
	std::pair<string, string> visit(NotEqualsToCommand& command);
	std::pair<string, string> visit(PlusCommand& command);
	std::pair<string, string> visit(PlusPlusCommand& command);
	std::pair<string, string> visit(ShowFunctionCommand& command);
	std::pair<string, string> visit(SmallerEqualsToCommand& command);
	std::pair<string, string> visit(SmallerThanCommand& command);
	std::pair<string, string> visit(TimesCommand& command);
};