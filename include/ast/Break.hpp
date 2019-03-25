#pragma once

#include "ast/Base.hpp"

namespace Fuse {

	class BreakAST : public ExprAST {
	public:
		BreakAST() { ; }
		
		std::shared_ptr<Fuse::Object> Eval();
		TypeAST GetType();
	private:
	};
	
	class ContinueAST : public ExprAST {
	public:
		ContinueAST() { ; }
		
		std::shared_ptr<Fuse::Object> Eval();
		TypeAST GetType();
	private:
	};
	
};