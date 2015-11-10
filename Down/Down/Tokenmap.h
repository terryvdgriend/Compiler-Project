#pragma once
struct TokenMap{
	static map<string, Token::iToken> get()
	{
		map<string, Token::iToken> mappert;
		//

		//
		//mappert["\\*\\*.+\\*\\*"] = Token::IDENTIFIER;
		return mappert;
	}
	
	

	
	static const map<string, Token::iToken> tm;

};

const map<string, Token::iToken> TokenMap::tm = TokenMap::get();
