#include "stdafx.h"
#include "Token.h"


Token::Token() : Level{ 1 }, next{ nullptr }, previous{ nullptr } //etc...
{
}

Token::Token(const Token & other)
{
	Text = other.Text;
	subType = other.subType;
	type = other.type;
	Partner = other.Partner;
	PositieInList = other.PositieInList;
	Regelnummer = other.Regelnummer;
	Positie = other.Positie;
	Level = other.Level;
}




void Token::Print(std::map<string, Token::iToken>& map)
{
	int space = 20;
	//
	string spacer = std::string(space - this->Text.size(), ' ');
	Text::print(to_string(this->PositieInList) + std::string(4, ' '));
	Text::print(to_string(this->Regelnummer) + std::string(4, ' '));
	Text::print(to_string(this->Positie) + std::string(4, ' '));
	Text::print(this->Text + spacer);
	Text::print(to_string(Level) + std::string(4, ' '));
	Text::print(this->getStringbyEnum(map, this->getEnum()) + spacer);
	if (this->getPartner() != nullptr)
		Text::print(to_string(this->getPartner()->PositieInList) + std::string(4, ' '));
	else
		Text::print(spacer);
	//
	Text::printLine("");

}

bool Token::operator!=(const Token & other)const
{
	if ((this->Text != other.Text) ||
		(this->Level != other.Level) ||
		(this->Positie != other.Positie) ||
		(this->PositieInList != other.PositieInList) ||
		(this->type != other.type) ||
		(this->subType != other.subType)||
		(this->Regelnummer != other.Regelnummer))
		return true;
	return false;
}

bool Token::operator!=(Token * other)
{
	if ((this->Text != other->Text) ||
		(this->Level != other->Level) ||
		(this->Positie != other->Positie) ||
		(this->PositieInList != other->PositieInList) ||
		(this->type != other->type) ||
		(this->subType != other->subType) ||
		(this->Regelnummer != other->Regelnummer))
		return true;
	return false;
}

bool Token::compare(Token* first, Token * other)
{
	if ((first->Text == other->Text) &&
		(first->Level == other->Level) &&
		(first->Positie == other->Positie) &&
		(first->PositieInList == other->PositieInList) &&
		(first->type == other->type) &&
		(first->subType == other->subType) &&
		(first->Regelnummer == other->Regelnummer))
		return true;
	return false;
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
	string descr = "Syntax error: '" + this->Text + "'";
	ErrorHandler::getInstance()->addError(make_shared<Error>(descr, "Unknown.MD", this->Regelnummer, this->Positie, ErrorType::error));
}

Token::~Token()
{
}
