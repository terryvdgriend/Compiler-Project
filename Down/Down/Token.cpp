#include "stdafx.h"
#include "Token.h"

Token::Token()
{
	_level		= 1;
	_next		= nullptr;
	_previous.reset();
	_subType	= IToken::NONE;
}

Token::Token(const shared_ptr<Token>& other)
{
	_text			= other->_text;
	_subType		= other->_subType;
	_type			= other->_type;
	_partner		= other->_partner;
	_positionInList	= other->_positionInList;
	_lineNumber		= other->_lineNumber;
	_position		= other->_position;
	_level			= other->_level;
	_scope			= other->_scope;
	_next			= nullptr;
	_previous.reset();
}

void Token::print(map<string, IToken>& tokenMap)
{
	int space = 20;
	string spacer = string(space - _text.substr(0, space).size(), ' ');

	Text::print(to_string(_positionInList) + string(4, ' '));
	Text::print(to_string(_lineNumber) + string(4, ' '));
	Text::print(to_string(_position) + string(4, ' '));
	Text::print(_text + spacer);
	Text::print(to_string(_level) + string(4, ' '));
	Text::print(getStringbyType(tokenMap, getType()) + spacer);

	if (getPartner() != nullptr)
	{
		if (shared_ptr<Token> t = _partner.lock())
		{
			Text::print(to_string(t->_positionInList) + string(4, ' '));
		}
	}
	else
	{
		Text::print(spacer);
	}
	Text::printLine("");
}

void Token::addError()
{
	string description = "Syntax error: '" + _text + "'";
    auto error = make_shared<Error>(description, "Unknown.MD", _lineNumber, _position, ErrorType::ERROR);
	ErrorHandler::getInstance()->addError(error);
}

bool Token::operator!=(const Token& other) const
{
	if (_text			!= other._text ||
		_level			!= other._level ||
		_position		!= other._position ||
		_positionInList != other._positionInList ||
		_type			!= other._type ||
		_subType		!= other._subType ||
		_scope			!= other._scope ||
		_lineNumber		!= other._lineNumber)
	{
		return true;
	}

	return false;
}

bool Token::operator!=(Token other)
{
	if (_text			!= other._text ||
		_level			!= other._level ||
		_position		!= other._position ||
		_positionInList	!= other._positionInList ||
		_type			!= other._type ||
		_subType		!= other._subType ||
		_lineNumber		!= other._lineNumber)
	{
		return true;
	}

	return false;
}

bool Token::operator==(Token other)
{
	if (_text == other._text &&
		_level == other._level &&
		_position == other._position &&
		_positionInList == other._positionInList &&
		_type == other._type &&
		_subType == other._subType &&
		_lineNumber == other._lineNumber)
	{
		return true;
	}

	return false;
}

bool Token::compare(shared_ptr<Token> first, shared_ptr<Token> other)
{
	if (first->_text			== other->_text &&
		first->_level			== other->_level &&
		first->_position		== other->_position &&
		first->_positionInList	== other->_positionInList &&
		first->_type			== other->_type &&
		first->_subType			== other->_subType &&
		first->_lineNumber		== other->_lineNumber)
	{
		return true;
	}

	return false;
}

string Token::getStringbyType(map<string, IToken>& tokenMap, IToken token)
{
	map<string, IToken>::const_iterator it;

	for (it = tokenMap.begin(); it != tokenMap.end(); ++it)
	{
		if (it->second == token)
		{
			return it->first;
		}
	}

	return "UNKNOWN";
}

string Token::getText()
{
	return _text;
}

void Token::setText(string text)
{
	_text = text;
}

IToken Token::getSubType()
{
	return _subType;
}

void Token::setSubType(IToken sub)
{
	_subType = sub;
}

IToken Token::getType()
{
	return _type;
}

void Token::setType(IToken type)
{
	_type = type;
}

shared_ptr<Token> Token::getPartner()
{
	if (shared_ptr<Token> t = _partner.lock())
	{
		return t;
	}

	return nullptr;
}

void Token::setPartner(shared_ptr<Token> partner)
{
	_partner = partner;
}

int Token::getLevel()
{
	return _level;
}

void Token::setLevel(int level)
{
	_level = level;
}

int Token::getLineNumber()
{
	return _lineNumber;
}

void Token::setLineNumber(int lineNumber)
{
	_lineNumber = lineNumber;
}

int Token::getPosition()
{
	return _position;
}

void Token::setPosition(int position)
{
	_position = position;
}

void Token::setPositionInList(int positionInList)
{
	_positionInList = positionInList;
}

int Token::getScope()
{
	return _scope;
}

void Token::setScope(int scope)
{
	_scope = scope;
}

shared_ptr<Token> Token::getNext()
{
	return _next;
}

void Token::setNext(shared_ptr<Token> next)
{
	_next = next;
}

shared_ptr<Token> Token::getPrevious()
{
	if (shared_ptr<Token> t = _previous.lock())
	{
		return t;
	}

	return nullptr;
}

void Token::setPrevious(shared_ptr<Token> previous)
{
	_previous = previous;
}