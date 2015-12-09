#pragma once
#include "Text.h"
#include "IToken.h"

class Token
{
	public:
		Token();
		Token(const shared_ptr<Token>& other);

		void print(map<string, IToken>& map);
		void addError();

		bool operator!=(const Token& other)const;
		bool operator!=(Token other);
		static bool compare(shared_ptr<Token> first, shared_ptr<Token> other);

		string getText();
		void setText(string text);
		IToken getSubType();
		void setSubType(IToken sub);
		IToken getType();
		void setType(IToken type);
		shared_ptr<Token> getPartner();
		void setPartner(shared_ptr<Token> partner);
		int	getLevel();
		void setLevel(int level);
		int	getLineNumber();
		void setLineNumber(int lineNumber);
		int	getPosition();
		void setPosition(int position);
		void setPositionInList(int positionInList);
		int	getScope();
		void setScope(int scope);
		string getStringbyEnum(map<string, IToken>& map, IToken token);
		shared_ptr<Token> getNext();
		void setNext(shared_ptr<Token> next);
		shared_ptr<Token> getPrevious();
		void setPrevious(shared_ptr<Token> previous);

	private:
		string _text;
		IToken _subType;
		IToken _type;
		shared_ptr<Token> _partner;
		int _positionInList;
		int _lineNumber;
		int _position;
		int _level;
		int _scope;

		shared_ptr<Token> _next;
		shared_ptr<Token> _previous;
};