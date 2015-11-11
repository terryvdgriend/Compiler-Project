#pragma once
#include "ActionNode.h"
#include "LinkedActionList.h"
template <typename T>
class SwitchNode :
	public ActionNode
{
public:
	SwitchNode()
	{
		defaultNode = nullptr;
	}


	~SwitchNode()
	{
	}
	void show(){
		cout << "Switch jump. \n";
	}
	void action();
	void accept(NodeVisitor& visitor)
	{
		visitor.visit(*this);
	}
public:
	LinkedActionList* defaultNodeList;
	std::map<T, LinkedActionList*> jumpMap;
};

