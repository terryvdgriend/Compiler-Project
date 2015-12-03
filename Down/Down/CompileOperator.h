#pragma once
#include "Compiler.h"
#include "CompileNextLevel.h"

class CompileOperator : public Compiler
{
	public:
		typedef map<Token::iToken, string> TokenMap;
		typedef list<shared_ptr<CompileNextLevel>> CompileNextLevelList;

		CompileOperator(shared_ptr<Compiler> pNextLevel);

		void compile(shared_ptr<LinkedList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end, 
					 shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore);
		
	protected:
		TokenMap tokenMap;

	private:
		shared_ptr<Compiler> pNextLevel;

		void fillRunList(const string& sFunctionName, shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& iBefore, vector<shared_ptr<ActionNode>>& beforeList);
		void fillNextLevelList(vector<shared_ptr<ActionNode>>& beforeArray, shared_ptr<Token>& current, shared_ptr<CompileNextLevel>& nextLevel, CompileNextLevelList& nextLevelList);
		void insertLastNextLevel(shared_ptr<Token>& end, shared_ptr<ActionNode>& before, shared_ptr<CompileNextLevel>& nextLevel, CompileNextLevelList& nextLevelList);
		void compileNextLevel(shared_ptr<LinkedList>& tokenList, shared_ptr<LinkedActionList>& listActionNodes, CompileNextLevelList& nextLevelList);
};