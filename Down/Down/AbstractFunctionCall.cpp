#include "stdafx.h"
#include "AbstractFunctionCall.h"

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

const AbstractFunctionCall::contentArray& AbstractFunctionCall::getContentArray() const
{
	return m_sContentArray;
}