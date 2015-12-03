#pragma once
#include "ActionNode.h"
#include "NodeVisitor.h"

class AbstractFunctionCall : public ActionNode
{
	public:
		void setArraySize(size_t newSize);
		void setAt(unsigned newPosition, const char* szText);
		vector<string>& getContentArrayNonConstant();

	protected:
		typedef vector<string> contentArray;
		const contentArray& getContentArray() const;

	private:
		contentArray m_sContentArray;
};