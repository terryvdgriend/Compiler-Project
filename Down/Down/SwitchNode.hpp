#pragma once
#include "ActionNode.h"
#include "LinkedActionList.h"
template<class T>
class SwitchNode :
	public ActionNode
{
public:
	SwitchNode()
	{
		defaultNodeList = nullptr;
	}


	~SwitchNode()
	{
	}
	void show(){
		cout << "Switch jump. \n";
	}
	void accept(NodeVisitor& visitor)
	{
		visitor.visit(*this);
	}
public:
	LinkedActionList* defaultNodeList;
	std::map<T , LinkedActionList*> jumpMap;
};

