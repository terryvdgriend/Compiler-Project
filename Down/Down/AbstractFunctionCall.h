#pragma once
#include "ActionNode.h"

class AbstractFunctionCall : public ActionNode
{
	public:
		void setArraySize(size_t newSize);
		void setAt(unsigned newPosition, const char* szText);
		vector<string>& getContentArrayNonConstant();
		shared_ptr<Token> getToken();

	protected:
		typedef vector<string> contentArray;
		const contentArray& getContentArray() const;
		weak_ptr<Token> _token;

	private:
		contentArray m_sContentArray;
};