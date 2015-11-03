#include "stdafx.h"
#include "Tokenizer.h"
#include "Format.h"
#include "LinkedList.h"
#include <iostream>
#include <regex>

// Dit mag weg bij release (TODO) 
#include <cstdio>
#include <ctime>
// ..


Tokenizer::Tokenizer()
{
	//
	mappert["\n"] = Token::NEWLINE;
	// 
	mappert["secret"] = Token::PRIVATE;
	mappert["#### if"] = Token::IF;
	mappert["#### else"] = Token::ELSE;
	mappert["#### else if"] = Token::ELIF;
	mappert["#### for"] = Token::FOR;
	mappert["#### foreach"] = Token::FOREACH;
	mappert["#### while"] = Token::WHILE;
	mappert["#### do"] = Token::DO;
	mappert["#### switch"] = Token::SWITCH;
	mappert["---"] = Token::FUNCTION_OPEN;
	mappert["___"] = Token::FUNCTION_CLOSE;
	mappert["("] = Token::CONDITION_OPEN;
	mappert[")"] = Token::CONDITION_CLOSE;
	mappert["--"] = Token::BODY_OPEN;
	mappert["__"] = Token::BODY_CLOSED;
	mappert["{"] = Token::ARRAY_OPEN;
	mappert["}"] = Token::ARRAY_CLOSED;
	mappert[":"] = Token::ASSIGNMENT;
	mappert["["] = Token::FUNCTION_DECLARE_OPEN;
	mappert["]"] = Token::FUNCTION_DECLARE_CLOSE;
	//
	mappert["is"] = Token::EQUALS;
	mappert["like"] = Token::EQUALS_TO;
	mappert["smaller than"] = Token::LESS_THAN;
	mappert["larger than"] = Token::LARGER_THAN;
	mappert["in"] = Token::IN;
	//
	mappert["_getal_"] = Token::NUMBER;
	mappert["_tekst_"] = Token::TEXT;
	mappert["_fact_"] = Token::BOOL;
	mappert["_variable_"] = Token::IDENTIFIER;
	mappert[","] = Token::SEPARATOR;
	mappert["_declaration_"] = Token::DECLARATION;
	mappert["_function_"] = Token::FUNCTION;
	mappert["_class_"] = Token::CLASS;
	mappert["_namespace_"] = Token::NAMESPACE;
	mappert["_comment_"] = Token::COMMENT;
	mappert["_switch-default_"] = Token::SWITCH_DEFAULT;
	mappert["_switch-case_"] = Token::SWITCH_CASE;
	//
	mappert["plus"] = Token::PLUS;
	mappert["increased"] = Token::PLUSPLUS;
	mappert["minus"] = Token::MINUS;
	mappert["decreased"] = Token::MINUSMINUS;
	mappert["divide"] = Token::DIVIDE;
	mappert["multiply"] = Token::TIMES;
	mappert["modulo"] = Token::MODULO;

	mappert["and gives"] = Token::RETURNVALUE;
	mappert["gets"] = Token::START_PARAMETERS;
	mappert[","] = Token::AND_PARA;
	mappert["_function-use_"] = Token::FUNCTIONUSE;
	mappert["_coming-params_"] = Token::COMINGPARAMETER;
	//
	//mappert["\\*\\*.+\\*\\*"] = Token::IDENTIFIER;


	regexert[std::string("\\d")] = Token::NUMBER; //NIET TE MAPPEN
	regexert[std::string("^\".*?\"$")] = Token::TEXT; //NIET TE MAPPEN
	regexert[std::string("(true|false)")] = Token::BOOL;
	regexert[std::string("^\\*\\*(\\w*)?\\*\\*$")] = Token::IDENTIFIER; //NIET TE MAPPEN __x__
	regexert[std::string("^(__(\\w*)__)$")] = Token::DECLARATION; //NIET TE MAPPEN __X__
	regexert[std::string("^(### (\\w*)$)")] = Token::FUNCTION;
	regexert[std::string("^(## (\\w*))$")] = Token::CLASS;
	regexert[std::string("^(# (\\w*))$")] = Token::NAMESPACE;
	regexert[std::string("^>.*\n")] = Token::COMMENT;
	regexert[std::string("\n")] = Token::NEWLINE;
	regexert[std::string("secret")] = Token::PRIVATE;
	regexert[std::string("^#### if$")] = Token::IF;
	regexert[std::string("^#### switch$")] = Token::SWITCH;
	regexert[std::string("^#### else$")] = Token::ELSE;
	regexert[std::string("^#### else if$")] = Token::ELIF;
	regexert[std::string("^#### for$")] = Token::FOR;
	regexert[std::string("^#### foreach$")] = Token::FOREACH;
	regexert[std::string("^#### while$")] = Token::WHILE;
	regexert[std::string("^#### do$")] = Token::DO;
	regexert[std::string("^:$")] = Token::ASSIGNMENT;
	regexert[std::string("^---$")] = Token::FUNCTION_OPEN;
	regexert[std::string("^___$")] = Token::FUNCTION_CLOSE;
	regexert[std::string("^\\[$")] = Token::FUNCTION_DECLARE_OPEN;
	regexert[std::string("^\\]$")] = Token::FUNCTION_DECLARE_CLOSE;
	regexert[std::string("^\\{$")] = Token::ARRAY_OPEN;
	regexert[std::string("^\\}$")] = Token::ARRAY_CLOSED;
	regexert[std::string("\\(")] = Token::CONDITION_OPEN;
	regexert[std::string("\\)")] = Token::CONDITION_CLOSE;
	regexert[std::string("^--$")] = Token::BODY_OPEN;
	regexert[std::string("^__$")] = Token::BODY_CLOSED;
	regexert[std::string("is")] = Token::EQUALS;
	regexert[std::string("like")] = Token::EQUALS_TO;
	regexert[std::string("larger than")] = Token::LARGER_THAN;
	regexert[std::string("smaller than")] = Token::LESS_THAN;
	regexert[std::string("in")] = Token::IN;
	regexert[std::string("plus")] = Token::PLUS;
	regexert[std::string("increased")] = Token::PLUSPLUS;
	regexert[std::string("minus")] = Token::MINUS;
	regexert[std::string("decreased")] = Token::MINUSMINUS;
	regexert[std::string("divide")] = Token::DIVIDE;
	regexert[std::string("^multiplied by|multiply$")] = Token::TIMES;
	regexert[std::string("modulo")] = Token::MODULO;
	regexert[std::string("^and gives$")] = Token::RETURNVALUE;
	regexert[std::string("^gets$")] = Token::START_PARAMETERS;
	regexert[std::string("^with$")] = Token::COMINGPARAMETER;
	regexert[std::string("^,")] = Token::AND_PARA;
	regexert[std::string("^default$")] = Token::SWITCH_DEFAULT;
	regexert[std::string("^case$")] = Token::SWITCH_CASE;


}

std::string Tokenizer::getKeyByValueMappert(Token::iToken tkn)
{
	for (std::map<std::string, Token::iToken>::const_iterator it = mappert.begin(); it != mappert.end(); ++it)
	{
		if (it->second == tkn)
			return it->first;
	}

	return "";
}

void Tokenizer::createTokenList(LinkedList& cTokenList, string codefromfile)
{
	Token  *pToken{};
	string s(codefromfile);
	smatch m;
	regex e("(#+ (?:else if|else|if|case|while|do|foreach|for|\\w+)|and gives|multiplied by|(^>.*\n)|(smaller|larger) than|\\w+|\\S+|\n)");
	regex se("\\*\\*.+\\*\\*");


	int rowNr = 1;
	int colNr = 1;
	int lvl = 1;
	int pInt = 0;
	bool isFunctionCall = false;


	std::clock_t startS;
	double durationS;
	startS = std::clock();

	while (regex_search(s, m, e))
	{
		std::clock_t start;
		double duration;
		start = std::clock();


		pToken = new Token;
		Token::iToken currentToken;
		string part = m[0];
		currentToken = getToken(part);


		/*duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
		if (duration != 0)
		{
			Text::PrintLine("GET_TOKEN(sec) : " + to_string(duration) + " bij token: " + to_string(currentToken));
		}*/

		// Geen token, dus add error
		if (currentToken == Token::NONE)
			ErrorHandler::getInstance()->addError(Error{ "Token not found :(", "unknown.MD", rowNr, colNr, Error::errorType::error });

		if (isFunctionCall){
			currentToken = Token::FUNCTIONUSE;
			isFunctionCall = false;
		}
		if (currentToken == Token::FUNCTION_DECLARE_OPEN)
			isFunctionCall = true;

		//New Lines
		if (currentToken == Token::NEWLINE)
		{
			colNr = 1;
			rowNr++;
		}

		pToken->setText((part));
		pToken->setLevel(lvl);
		pToken->setPositie(colNr);
		pToken->setPositieInList(pInt);
		pToken->setRegelnummer(rowNr);
		pToken->setEnum(currentToken);
		pToken->setPartner(nullptr);

		//Add + Next
		cTokenList.add(pToken);

		//Levels
		if (currentToken == Token::BODY_OPEN || currentToken == Token::CONDITION_OPEN || currentToken == Token::FUNCTION_OPEN)
		{
			lvl++;
		}

		//++ col
		colNr += part.size() + 1;
		pInt++;

		////Levels
		if (currentToken == Token::BODY_CLOSED || currentToken == Token::CONDITION_CLOSE || currentToken == Token::FUNCTION_CLOSE)
		{
			lvl--;
		}

		CheckStack(*pToken, lvl);

		s = m.suffix().str();
	}

	durationS = (std::clock() - startS) / (double)CLOCKS_PER_SEC;
	Text::PrintLine("END(sec) : " + to_string(durationS) + " <<<<<<< ");

	CheckRemainingStack();
	checkRemainingErrors();
}

void Tokenizer::checkRemainingErrors()
{
	if (this->stack.size() > 0)
	{
		tokenError = true;
		while (this->stack.size() > 0)
		{
			Token* token = this->stack.top();
			this->stack.pop();
			token->addError();
		}
	}
}

void Tokenizer::printTokenList(LinkedList& cTokenList)
{
	Text::PrintLine("POSITIELIJST - REGELNR - POSITIE - TEXT - LEVEL - PARTNER");
	Token* start = cTokenList.first;
	while (start != nullptr){
		start->Print(this->mappert);
		start = start->next;
	}
}

void Tokenizer::CheckRemainingStack(){
	if (this->stack.size() > 0 && this->stack.top()->getEnum() == Token::IF){
		this->stack.pop();
	}
}


void Tokenizer::CheckStack(Token& token, int &lvl){
	CheckCondition(token, lvl);
	CheckBrackets(token, lvl);
};

void Tokenizer::CheckCondition(Token& token, int &lvl){
	if (token.getEnum() == Token::DO)
	{
		this->stack.push(&token);
	}
	if (token.getEnum() == Token::WHILE){
		if (this->stack.size() > 0 && this->stack.top()->getEnum() == Token::DO){
			Token* stackToken = this->stack.top();
			token.setPartner(stackToken);
			stackToken->setPartner(&token);
			this->stack.pop();
		}
	}
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

void Tokenizer::CheckBrackets(Token& token, int &lvl)
{
	if (token.getEnum() == Token::BODY_OPEN || token.getEnum() == Token::CONDITION_OPEN || token.getEnum() == Token::FUNCTION_OPEN)
	{
		this->stack.push(&token);
	}
	else if (token.getEnum() == Token::BODY_CLOSED || token.getEnum() == Token::CONDITION_CLOSE || token.getEnum() == Token::FUNCTION_CLOSE)
	{
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
				(token.getEnum() == Token::FUNCTION_CLOSE && this->stack.top()->getEnum() == Token::FUNCTION_OPEN) ||
				(token.getEnum() == Token::CONDITION_CLOSE && this->stack.top()->getEnum() == Token::CONDITION_OPEN))
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

struct check_x
{
	check_x(Token::iToken x) : x_(x) {}
	bool operator()(const std::pair<int, Token::iToken>& v) const
	{
		return  v.second == x_;// v.second.x == x_;
	}
private:
	Token::iToken x_;
};

Token::iToken Tokenizer::getToken(std::string token){
	

	Token::iToken  asd = std::find_if(regexert.begin(), regexert.end(), check_x(token))->second;
	return asd;





	/*smatch m;
	typedef std::map<std::string, Token::iToken>::iterator it_type;
	for (it_type iterator = regexert.begin(); iterator != regexert.end(); iterator++) 
	{
		
		regex e(iterator->first);
		regex_search(token, m, e);
		if (m.size() != 0)
		{
			return iterator->second;
		}

	}*/



	/*
	std::string input("01/02/2003 blahblah 04/23/1999 blahblah 11/13/1981");
	std::regex ws_re("\\s+");

	// iterate over the days, months and years in the input
	int const sub_matches[] = { 2, 1, 3 }; // day, month, year
	sregex_token_iterator begin(input.begin(), input.end(), ws_re, sub_matches), end;
	*/
	return Token::NONE;
}

std::string Tokenizer::getKeywordsAsJson()
{
	std::string JSON = "[";
	int size = (int)mappert.size();
	int i = 0;
	for (std::map<std::string, Token::iToken>::iterator it = mappert.begin(); it != mappert.end(); ++it)
	{
		if ((*it).second == Token::NEWLINE)
		{
			i++;
			continue;
		}
		JSON += "{\"keyword\":\"" + (*it).first + "\"}";

		if (i < size - 1)
			JSON += ",";
		i++;
	}
	JSON += "]";
	return JSON;
}


Tokenizer::~Tokenizer()
{
}
