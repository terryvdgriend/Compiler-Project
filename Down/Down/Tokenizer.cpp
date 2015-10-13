#include "stdafx.h"
#include "Tokenizer.h"
#include "Format.h"
#include "LinkedList.h"
#include <iostream>
#include <regex>

Tokenizer::Tokenizer()
{
	//
	mappert["\n"] = Token::NEWLINE;
	// 
	mappert["###"] = Token::CLASS;
	mappert["#### if"] = Token::IF;
	mappert["#### else"] = Token::ELSE;
	mappert["#### else if"] = Token::ELIF;
	mappert["___"] = Token::BODY_CLOSED;
	mappert["---"] = Token::BODY_OPEN;
	mappert["is"] = Token::EQUALS;
	mappert["like"] = Token::EQUALS_TO;
	//
	mappert["_number_"] = Token::NUMBER;
	mappert["_text_"] = Token::TEXT;
	mappert["_fact_"] = Token::BOOL;
	//
	mappert["plus"] = Token::PLUS;
	mappert["minus"] = Token::MINUS;
	mappert["divide"] = Token::DIVIDE;
	mappert["multiply"] = Token::TIMES;
	mappert["modulo"] = Token::NONE;
	//
	//mappert["\\*\\*.+\\*\\*"] = Token::IDENTIFIER;
}

void Tokenizer::createTokenList(LinkedList& cTokenList, string codefromfile)
{
	Token  *pToken;

	string s(codefromfile);
	smatch m;
	regex e("(#+ (?:else if|else|if|case)|\\w+|\\S+|\n)");
	regex se("\\*\\*.+\\*\\*");
	// (#+ (?:else if|else|if|case)|\w+|\S+)
	// M: (""|'.'\d+\.\d+|\w|\S|\n)
	// 

	int rowNr = 1;
	int colNr = 1;
	int lvl = 1;
	int pInt = 0;

	while (regex_search(s, m, e))
	{
		pToken = new Token;
		Token::iToken currentToken;
		string part = m[0];
		//Check identifier
		smatch sm;
		regex_search(part, sm, se);
		if (sm.size() != 0)
			currentToken = Token::IDENTIFIER;
		else
			currentToken = mappert[part];

		//New Lines
		if (currentToken == Token::NEWLINE)
		{
			colNr = 1;
			rowNr++;
			s = m.suffix().str();
			continue;
		}

		//Levels
		//if (currentToken == Token::BODY_OPEN)
		//{
		//	lvl++;
		//	stack.push_front(pToken);
		//}

		
		pToken->setText((part));
		pToken->setLevel(lvl); 
		pToken->setPositie(colNr);
		pToken->setPositieInList(pInt);
		pToken->setRegelnummer(rowNr);
		pToken->setEnum(currentToken);
		

		//++ col
		colNr += part.size() + 1;
		pInt++;
		
		////Levels
		//if (currentToken == Token::BODY_CLOSED)
		//{
		//	lvl--;
		//	//Token tok = *cTokenList.back();
		//	//pToken->setPartner(tok); // TODO
		//	stack.pop_front();
		//}

		//Add + Next
		cTokenList.add(pToken);
		//
		CheckStack(*pToken,lvl);
		s = m.suffix().str();
	}
	CheckRemainingStack();
}

void Tokenizer::printTokenList(LinkedList& cTokenList)
{
	if (this->stack.size() > 0){
		tokenError = true;
		while (this->stack.size() > 0){
			Token* token = this->stack.top();
			this->stack.pop();
			token->PrintError();
		}
	}
	else{
		Text::PrintLine("POSITIELIJST - REGELNR - POSITIE - TEXT - LEVEL - PARTNER");
		Token* start = cTokenList.first;
		while (start != nullptr){
			start->Print();
			start = start->next;
		}
	}
}

void Tokenizer::CheckRemainingStack(){
	if (this->stack.size() > 0 && this->stack.top()->getEnum() == Token::IF){
		this->stack.pop();
	}
}

void Tokenizer::CheckStack(Token& token, int& lvl){
	CheckCondition(token, lvl);
	CheckBrackets(token, lvl);
};

void Tokenizer::CheckCondition(Token& token, int& lvl){
	if (token.getEnum() == Token::IF)
	{
		if (this->stack.size() > 0 && this->stack.top()->getEnum() == Token::IF)
		{
			this->stack.pop();
		}
		this->stack.push(&token);
	}
	if (token.getEnum() == Token::ELSE)
	{
		if (this->stack.size() > 0 && this->stack.top()->getEnum() == Token::IF)
		{
			Token* stackToken = this->stack.top();
			token.setPartner(stackToken);
			stackToken->setPartner(&token);
			this->stack.pop();
		}
		else if (this->stack.size() > 0 && this->stack.top()->getEnum() == Token::ELIF)
		{
			Token* stackToken = this->stack.top();
			Token* partner = stackToken->getPartner();
			if (partner == nullptr){
				this->stack.push(&token);
			}
			else{
				while (partner->getEnum() != Token::IF){
					partner = partner->getPartner();
				}
				token.setPartner(partner);
				stackToken->setPartner(&token);
				this->stack.pop();
			}

		}
		else{
			this->stack.push(&token);
		}
	}
	if (token.getEnum() == Token::ELIF)
	{
		if (this->stack.size() > 0 && this->stack.top()->getEnum() == Token::IF)
		{
			Token* stackToken = this->stack.top();
			token.setPartner(stackToken);
			stackToken->setPartner(&token);
			this->stack.pop();
			this->stack.push(&token);
		}
		else if (this->stack.size() > 0 && this->stack.top()->getEnum() == Token::ELIF)
		{
			Token* stackToken = this->stack.top();
			Token* partner = stackToken->getPartner();
			while (partner->getEnum() != Token::IF){
				partner = partner->getPartner();
			}
			token.setPartner(partner);
			stackToken->setPartner(&token);
			this->stack.pop();
			this->stack.push(&token);
		}
		else{
			this->stack.push(&token);
		}
	}
};

void Tokenizer::CheckBrackets(Token& token, int& lvl)
{
	if (token.getEnum() == Token::BODY_OPEN || token.getEnum() == Token::CONDITION_OPEN)
	{
		this->stack.push(&token);
		lvl++;
	}
	else if (token.getEnum() == Token::BODY_CLOSED || token.getEnum() == Token::CONDITION_CLOSE)
	{
		lvl--;
		if (this->stack.size() > 0)
		{
			if ((token.getEnum() == Token::BODY_CLOSED && this->stack.top()->getEnum() == Token::IF) && token.getLevel() == this->stack.top()->getLevel())
			{
				if (token.next != nullptr)
				{
					if (token.next->getEnum() != Token::ELSE)
					{
						this->stack.pop();
					}
				}
			}
			if ((token.getEnum() == Token::BODY_CLOSED && this->stack.top()->getEnum() == Token::BODY_OPEN) ||
				(token.getEnum() == Token::CONDITION_CLOSE & this->stack.top()->getEnum() == Token::CONDITION_OPEN))
			{
				token.setLevel(lvl);
				Token* stackToken = this->stack.top();
				token.setPartner(stackToken);
				stackToken->setPartner(&token);
				this->stack.pop();
			}
		}
	}
};


Tokenizer::~Tokenizer()
{

}
