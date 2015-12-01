#pragma once
#include "Compiler.h"
#include "CompileNextLevel.h"

class CompileOperator : public Compiler
{
	public:
		typedef map<Token::iToken, string> TokenMap;
		typedef list<CompileNextLevel> CompileNextLevelList;

		CompileOperator(shared_ptr<Compiler> pNextLevel);

		void compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
		
		TokenMap& getTokenMap();
		
	protected:
		shared_ptr<Compiler> pNextLevel;

	private:
		TokenMap tokenMap;

		void fillRunList(const string& sFunctionName, LinkedActionList& listActionNodes, ActionNode& iBefore, vector<ActionNode*>* beforeList);
		void fillNextLevelList(vector<ActionNode*>* beforeArray, Token& current, CompileNextLevel& nextLevel, CompileNextLevelList& nextLevelList);
		void insertLastNextLevel(Token& end, ActionNode& before, CompileNextLevel& nextLevel, CompileNextLevelList& nextLevelList);
		void compileNextLevel(LinkedList& tokenList, LinkedActionList& runList, CompileNextLevelList& nextLevelList);
};