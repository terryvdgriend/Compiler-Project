#pragma once
#include "Compiler.h"
#include "CompileNextLevel.h"

class CompileOperator : public Compiler
{
	public:
		typedef unique_ptr<map<Token::iToken, string>> TokenMap;
		typedef shared_ptr<list<shared_ptr<CompileNextLevel>>> CompileNextLevelList;

		CompileOperator(shared_ptr<Compiler> pNextLevel);

		void compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
		
	protected:
		TokenMap tokenMap;

	private:
		shared_ptr<Compiler> pNextLevel;

		void fillRunList(const string& sFunctionName, LinkedActionList& listActionNodes, ActionNode& iBefore, vector<shared_ptr<ActionNode>>& beforeList);
		void fillNextLevelList(vector<shared_ptr<ActionNode>>& beforeArray, Token& current, CompileNextLevel& nextLevel, CompileNextLevelList& nextLevelList);
		void insertLastNextLevel(Token& end, ActionNode& before, CompileNextLevel& nextLevel, CompileNextLevelList& nextLevelList);
		void compileNextLevel(LinkedList& tokenList, LinkedActionList& runList, CompileNextLevelList& nextLevelList);
};