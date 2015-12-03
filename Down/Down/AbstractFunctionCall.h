#pragma once
#include "NodeVisitor.h"

class AbstractFunctionCall : public ActionNode
{
	public:
		void setArraySize(size_t);
		void setAt(unsigned, const char*);
		vector<string>& getContentArrayNonConstant();
		Token* getToken() { return this->token; };
	protected:
		typedef vector<string> contentArray;
		const contentArray& getContentArray() const;
		Token* token;
	private:
		contentArray m_sContentArray;
		
};