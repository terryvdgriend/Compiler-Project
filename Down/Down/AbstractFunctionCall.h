#pragma once
#include "ActionNode.h"
class AbstractFunctionCall :
	public ActionNode
{

protected:
	typedef std::vector<std::string> contentArray;

protected:
	virtual const contentArray &getContentArray()   const;

private:
	contentArray                m_sContentArray;
public:
	virtual void                setArraySize(size_t);
	virtual void                setAt(unsigned, const char*);
public:
	AbstractFunctionCall();
	virtual void  Show();
	virtual void  Action();
	virtual void  Accept(NodeVisitor visitor);
	~AbstractFunctionCall();
};

