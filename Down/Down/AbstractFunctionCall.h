#pragma once
#include "ActionNode.h"

class AbstractFunctionCall : public ActionNode
{
	public:
		void setArraySize(size_t);
		void setAt(unsigned, const char*);

	protected:
		typedef vector<string> contentArray;
		const contentArray &getContentArray() const;

	private:
		contentArray m_sContentArray;
};