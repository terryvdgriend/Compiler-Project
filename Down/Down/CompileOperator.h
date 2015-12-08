#pragma once
#include "Compiler.h"
#include "CompileNextLevel.h"

class CompileOperator : public Compiler
{
	public:
		typedef map<IToken, string> TokenMap;
		typedef list<CompileNextLevel> CompileNextLevelList;

		CompileOperator(shared_ptr<Compiler> nextlevel);

		void compile(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end,
					 shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore);
		virtual shared_ptr<Compiler> create() = 0;
		
	protected:
		TokenMap tokenMap;

	private:
		shared_ptr<Compiler> pNextLevel;

		void fillRunList(const string& sFunctionName, shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& iBefore, 
						 vector<shared_ptr<ActionNode>>& beforeArray, shared_ptr<Token>& token);
		void fillNextLevelList(vector<shared_ptr<ActionNode>>& beforeArray, shared_ptr<Token>& current, CompileNextLevel& nextLevel,
							   CompileNextLevelList& nextLevelList);
		void insertLastNextLevel(shared_ptr<Token>& end, shared_ptr<ActionNode>& before, CompileNextLevel& nextLevel, 
								 CompileNextLevelList& nextLevelList);
		void compileNextLevel(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<LinkedActionList>& listActionNodes,
							  CompileNextLevelList& nextLevelList);
};