#include "stdafx.h"
#include "CompileComparison.h"


CompileComparison::CompileComparison()
{
	std::map<Token::iToken, string> tokenMap = getTokenMap();
	//tokenMap[Token::AND] = "$&&"; //TODO deze 2 
	//tokenMap[Token::OR] = "$||";
}


CompileComparison::~CompileComparison()
{
}
