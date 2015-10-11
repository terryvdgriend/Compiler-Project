#include "stdafx.h"
#include "Token.h"


Token::Token() : Text{ "NotSet" }, Level{ 1 } //etc..
{
}

void Token::Print()
{
	int space = 15;
	//
	string spacer = std::string(space - this->Text.size(), ' ');
	Text::Print(this->Text + spacer);
	Text::Print(to_string(this->Regelnummer) + std::string(4, ' '));
	Text::Print(to_string(this->Positie) + std::string(4, ' '));
	Text::Print(to_string(Level) + std::string(4, ' '));
	//
	Text::PrintLine("");

}

Token::~Token()
{
}
