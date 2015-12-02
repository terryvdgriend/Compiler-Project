#pragma once
#include "Function.h"

class FunctionHandler
{
	public:
		void addFunction(shared_ptr<Function>& funcion);

		static shared_ptr<FunctionHandler> getInstance();
		shared_ptr<list<shared_ptr<Function>>> getFunctions();

	private:
		static shared_ptr<FunctionHandler> handler;
		shared_ptr<list<shared_ptr<Function>>> functions;

		FunctionHandler();
};