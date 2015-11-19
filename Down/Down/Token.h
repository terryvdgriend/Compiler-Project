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
		NONE = 0,
		NEWLINE,
		PLUS,
		MINUS,
		TIMES,
		DIVIDE,
		LESS_THAN,
		LARGER_THAN,
		IDENTIFIER, // VARB **i**
		NUMBER, // 1-2-3-4
		TEXT, // "txt" 
		FACT,
		TYPE_NUMBER,
		TYPE_TEXT,
		TYPE_FACT,
		CONDITION_OPEN,  // ( -> simuleren?
		CONDITION_CLOSE, // ) -> simuleren?
		FUNCTION_OPEN,  // ( -> simuleren?
		FUNCTION_CLOSE, // ) -> simuleren?
		BODY_OPEN, // ____
		BODY_CLOSED,// ____
		DO,
		WHILE,
		IF,
		ELSE,
		ELIF,
		EQUALS, // IS
		EQUALS_TO, // LIKE
		AND_PARA, // , (comma)
		CLASS,
		BOOL,
		MODULO,
		PRIVATE,
		FOR,
		FOREACH,
		PRINT,
		PRINTUP,
		PLUSPLUS,
		MINUSMINUS,
		SEPARATOR,
		DECLARATION,
		IN,
		FUNCTION_CALL,
		FUNCTION_DECLARE,
		NAMESPACE,
		COMMENT,
		ASSIGNMENT,
		RETURNVALUE,
		START_PARAMETERS,
		FUNCTION_DECLARE_OPEN,
		FUNCTION_DECLARE_CLOSE,
		FUNCTIONUSE,
		COMINGPARAMETER,
		ARRAY_OPEN,
		ARRAY_CLOSE,
		SWITCH_CASE,
		SWITCH_DEFAULT,
		SWITCH,
		ANY
	};

public:
	Token();
	~Token();

public:
	virtual void    setText(std::string txt){ Text = txt; };
	virtual void    setSub(iToken st) { subType = st; };
	virtual void    setEnum(iToken itoken){ type = itoken; };
	virtual void    setPartner(Token* partner){ Partner = partner; };
	virtual void    setPositieInList(int txt){ PositieInList = txt; };
	virtual void    setRegelnummer(int txt){ Regelnummer = txt; };
	virtual void    setPositie(int txt){ Positie = txt; };
	virtual void    setLevel(int txt){ Level = txt; };


public:
	std::string     getText() { return Text; };
	iToken		    getSub() { return subType; };
	iToken          getEnum(){ return type; };
	Token*			getPartner()   { return Partner; };
	int				getLevel() { return Level; };
	int				getLineNumber(){ return Regelnummer; };
	int				getPositie(){ return Positie; };
	std::string getStringbyEnum(std::map<string, Token::iToken>& map, Token::iToken token);
	void Print(std::map<string, Token::iToken>& map);
	void addError();
	Token*			next;
	Token*			previous;

private:
	std::string     Text;
	iToken			subType;
	iToken          type;
	Token*			Partner;
	int PositieInList;
	int Regelnummer;
	int Positie;
	int Level;
};

