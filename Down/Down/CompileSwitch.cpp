#include "stdafx.h"
#include "CompileSwitch.h"
#include "DoNothingNode.h"
#include "CompileFactory.h"
#include "TokenExpectation.h"


CompileSwitch::CompileSwitch()
{
	_compiledStatement = nullptr;
	SwitchNode = nullptr;
}

void CompileSwitch::ConnectLists() {

}

void CompileSwitch::Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore) {
	
}


CompileSwitch::~CompileSwitch()
{
}
