#pragma once
#include "Function.h"

class FunctionHandler
{
	public:
		#ifdef _WIN32
		void FunctionHandler::addFunction(shared_ptr<Function>& funcion);
		#else
		void addFunction(shared_ptr<Function>& funcion);
		#endif

		static shared_ptr<FunctionHandler> getInstance();
		shared_ptr<list<shared_ptr<Function>>> getFunctions();

	private:
		static shared_ptr<FunctionHandler> handler;
		shared_ptr<list<shared_ptr<Function>>> functions;

		FunctionHandler();
};