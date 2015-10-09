#pragma once
#include <string>
#include <list>
#include <map>

using namespace std;

class Token
{
public:
	enum iToken {
		NONE = 0,
		PLUS,
		MINUS,
		TIMES,
		DIVIDE,
		LESS_THAN,
		LARGER_THAN,
		IDENTIFIER, // VARB (x, z )
		NUMBER,
		TEXT,
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
	virtual void    setPartner(iterator& partner){ *Partner = partner; };

public:
	std::string     getText() { return Text; };
	iToken          getEnum(){ return type; };
	
	iterator       *getPartner()   { return Partner; };

private:
	std::string     Text;
	iToken          type;
	iterator       *Partner;
	
	//Wat niet in de copy paste zat: (ook nog geen set;get;)
	int PositieInList;
	int Regelnummer;
	int Positie;
	int Level;
};

