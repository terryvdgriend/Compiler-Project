#pragma once
#include <string>
#include <list>
#include <stack>
#include <map>
#include "Text.h"

using namespace std;

class Token
{

public:
	enum iToken {
		// PROG ONLY
		NONE = 0,
		NEWLINE,
		// REALDEAL
		PLUS,
		MINUS,
		TIMES,
		DIVIDE,
		LESS_THAN,
		LARGER_THAN,
		IDENTIFIER, // VARB **i**
		NUMBER, // 1-2-3-4
		TEXT, // "txt" 
		CONDITION_OPEN,  // ( -> simuleren?
		CONDITION_CLOSE, // ) -> simuleren?
		BODY_OPEN, // ____
		BODY_CLOSED,// ____
		WHILE,
		IF,
		ELSE,
		ELIF,
		EQUALS, // IS
		EQUALS_TO, // LIKE
		AND_PARA, // , (comma)
		CLASS,
		BOOL,
	};


public:
	typedef std::list<Token*>   TokenList;
	typedef TokenList::iterator iterator;

public:
	Token();
	~Token();

public:
	virtual void    setText(std::string txt){ Text = txt; };
	virtual void    setEnum(iToken itoken){ type = itoken; };
	virtual void    setPartner(Token* partner){ Partner = partner; };
	virtual void    setPositieInList(int txt){ PositieInList = txt; };
	virtual void    setRegelnummer(int txt){ Regelnummer = txt; };
	virtual void    setPositie(int txt){ Positie = txt; };
	virtual void    setLevel(int txt){ Level = txt; };


public:
	std::string     getText() { return Text; };
	iToken          getEnum(){ return type; };
	Token*			getPartner()   { return Partner; };
	int				getLevel() { return Level; };
	void Print();
	Token*			next;
	Token*			previous;

private:
	std::string     Text;
	iToken          type;
	Token*			Partner;
	int PositieInList;
	int Regelnummer;
	int Positie;
	int Level;
};

