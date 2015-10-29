#include "stdafx.h"
#include "AbstractFunctionCall.h"

void AbstractFunctionCall::setArraySize(size_t nSize)
{
	m_sContentArray.resize(nSize);
}

void AbstractFunctionCall::setAt(unsigned nPosition, const char* szText)
{
	m_sContentArray[nPosition] = szText;
}

const AbstractFunctionCall::contentArray&

AbstractFunctionCall::getContentArray() const
{
	return m_sContentArray;
}