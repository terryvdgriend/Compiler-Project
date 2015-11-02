#include "stdafx.h"
#include "Token.h"


Token::Token() : Level{ 1 }, next{ nullptr }, previous{ nullptr } //etc...
{
}



void Token::Print(std::map<string, Token::iToken>& map)
{
	int space = 20;
	//
	string spacer = std::string(space - this->Text.size(), ' ');
	Text::Print(to_string(this->PositieInList) + std::string(4, ' '));
	Text::Print(to_string(this->Regelnummer) + std::string(4, ' '));
	Text::Print(to_string(this->Positie) + std::string(4, ' '));
	Text::Print(this->Text + spacer);
	Text::Print(to_string(Level) + std::string(4, ' '));
	Text::Print(this->getStringbyEnum(map, this->getEnum()) + spacer);
	if (this->getPartner() != nullptr)
		Text::Print(to_string(this->getPartner()->PositieInList) + std::string(4, ' '));
	else
		Text::Print(spacer);
	//
	Text::PrintLine("");

}

std::string Token::getStringbyEnum(std::map<string, Token::iToken>& map, Token::iToken token){
	std::map<std::string, Token::iToken>::const_iterator it;
	for (it = map.begin(); it != map.end(); ++it){
		//if (it != nullptr)
		if (it->second == token)
			return it->first;
	}
	return "UNKNOWN";
}


void Token::addError() 
{
	std::string descr = "Syntax error: '" + this->Text + "'";
	Error err{ descr, "Unknown.MD", this->Regelnummer, this->Positie, Error::errorType::error };
	ErrorHandler::getInstance()->addError(err);
}

Token::~Token()
{
}
