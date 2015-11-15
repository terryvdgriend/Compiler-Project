#pragma once
#include "Compiler.h"
#include "CompileNextLevel.h"

class CompileOperator : public Compiler
{
protected:
	Compiler *pNextLevel;
public:
	CompileOperator(Compiler* pNext);
	void Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
	~CompileOperator();
	typedef std::map<Token::iToken, string> TokenMap;

	TokenMap &getTokenMap();
public:
	typedef std::list<CompileNextLevel> CompileNextLevelList;

private:
	TokenMap tokenMap;

	void fillRunList(const std::string&, LinkedActionList&, ActionNode&, std::vector<ActionNode*>* beforeArray);
	void fillNextLevelList(std::vector<ActionNode*>* beforeArray, Token&, CompileNextLevel&, CompileNextLevelList&);
	void insertLastNextLevel(Token&, ActionNode&, CompileNextLevel&, CompileNextLevelList&);
	void compileNextLevel(LinkedList& cTokenList, LinkedActionList& cRunList, CompileNextLevelList& cNextLevelList);
};

