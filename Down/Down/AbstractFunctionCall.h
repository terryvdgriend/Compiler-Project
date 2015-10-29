#pragma once
#include "ActionNode.h"

class NextNodeVisitor;

class AbstractFunctionCall : public ActionNode
{
	public:
		void setArraySize(size_t);
		void setAt(unsigned, const char*);
		virtual void show() = 0;
		virtual void action() = 0;
		virtual void accept(NextNodeVisitor& visitor) = 0;

	protected:
		typedef vector<string> contentArray;
		const contentArray &getContentArray() const;

	private:
		contentArray  m_sContentArray;
};