#include "stdafx.h"
#include "Token.h"


Token::Token() : Text{ "NotSet" }, Level{ 1 }, next{ nullptr }, previous{nullptr} //etc..
{
}



void Token::Print()
{
	int space = 15;
	//
	string spacer = std::string(space - this->Text.size(), ' ');
	Text::Print(to_string(this->PositieInList) + std::string(4, ' '));
	Text::Print(to_string(this->Regelnummer) + std::string(4, ' '));
	Text::Print(to_string(this->Positie) + std::string(4, ' '));
	Text::Print(this->Text + spacer);
	Text::Print(to_string(Level) + std::string(4, ' '));
	if (this->getPartner() != nullptr)
		Text::Print(to_string(this->getPartner()->PositieInList) + std::string(4, ' '));
	else
		Text::Print(spacer);
	//
	Text::PrintLine("");

}

void Token::PrintError()
{
	int space = 15;
	//
	string spacer = std::string(space - this->Text.size(), ' ');
	Text::Print("Error at line:" + std::string(4, ' '));
	Text::Print(to_string(this->Regelnummer) + std::string(4, ' '));
	Text::Print("token error:" + std::string(4, ' '));
	Text::Print(this->Text + spacer);
	//
	Text::PrintLine("");

}

Token::~Token()
{
}
