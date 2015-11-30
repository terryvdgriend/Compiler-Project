#include "stdafx.h"
#include "CompileFactory.h"
#include "CompilerHeader.h"

CompileFactory::CompileFactory()
{
	mappert[Token::IF] = new CompileIf();
	mappert[Token::WHILE] = new CompileWhile();
	mappert[Token::DO] = new CompileDoWhile();
	//mappert[Token::FUNCTION_DECLARE_OPEN] = new CompileFunction();//Bestaande functie
	mappert[Token::FUNCTION_DECLARE_OPEN] = new CompileGetFunction();//Bestaande functie
	mappert[Token::FUNCTION_OPEN] = new CompileUserFunction(); // aangemaakte functie
	mappert[Token::IDENTIFIER] = new CompileEquals();
	mappert[Token::ARRAY_OPEN] = new CompileArray();
	mappert[Token::SWITCH] = new CompileSwitch();
	mappert[Token::NEWLINE] = nullptr;
}

Compiler * CompileFactory::CreateCompileStatement(Token& tknzr)
{
	std::map<Token::iToken, Compiler*>::iterator it = mappert.find(tknzr.getEnum());
	if (it != mappert.end()){
		if (it->second != nullptr) {
			if (tknzr.getSub() == Token::TYPE_NUMBER_ARRAY || tknzr.getSub() == Token::TYPE_TEXT_ARRAY || tknzr.getSub() == Token::TYPE_FACT_ARRAY)
			{
				if (tknzr.previous->getEnum() == Token::NEWLINE && tknzr.next->getEnum() == Token::ARRAY_OPEN) { return CompileAddArrayItem().Create(); }
				else { return CompileGetArrayItem().Create(); }
			}
			return it->second->Create(); // Create is een copy maken
		}
		return nullptr;
	}
		
	//
	ErrorHandler::getInstance()->addError("Incorrect syntax (CompileFactory): " + tknzr.getText(), &tknzr);

	return nullptr;
}


CompileFactory::~CompileFactory()
{
}
