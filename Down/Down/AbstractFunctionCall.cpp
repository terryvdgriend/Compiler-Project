#include "stdafx.h"
#include "AbstractFunctionCall.h"
#include "MandatoryNodeIncludes.h"

void AbstractFunctionCall::setArraySize(size_t nSize)
{
	m_sContentArray.resize(nSize);
}

void AbstractFunctionCall::setAt(unsigned newPosition, const char* szText)
{
	m_sContentArray[newPosition] = szText;
}

vector<string>& AbstractFunctionCall::getContentArrayNonConstant()
{
	return m_sContentArray;
}

shared_ptr<Token> AbstractFunctionCall::getToken()
{
	if (shared_ptr<Token> t = _token.lock())
	{
		return t;
	}

	return nullptr;
}

const AbstractFunctionCall::contentArray& AbstractFunctionCall::getContentArray() const
{
	return m_sContentArray;
}