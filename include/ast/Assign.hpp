#pragma once

#include "ast/Base.hpp"

namespace Fuse {

	class AssignAST : public ExprAST {
	public:
		AssignAST(std::unique_ptr<ExprAST> _LHS_Expr, std::unique_ptr<ExprAST> _RHS_Expr):
			LHS_Expr(std::move(_LHS_Expr)), RHS_Expr(std::move(_RHS_Expr)) { ; }
		
		std::shared_ptr<Fuse::Object> Eval();
		TypeAST GetType();
	private:
		std::unique_ptr<ExprAST> LHS_Expr, RHS_Expr;
	};
	
};