#pragma once

#include "ast/Base.hpp"
#include "Lexer.hpp"

namespace Fuse {

	// expr OPERATOR expr
	// eg. foo(1) + 5
	class BinaryExprAST : public ExprAST {
	public:
		BinaryExprAST(std::unique_ptr<ExprAST> _lhs, std::unique_ptr<ExprAST> _rhs, OPERATORS _op):
			LHS(std::move(_lhs)), RHS(std::move(_rhs)), Operator(_op) { ; }
	
		std::shared_ptr<Fuse::Object> Eval();
	private:
		std::unique_ptr<ExprAST> LHS, RHS;
		OPERATORS Operator;
		
		TypeAST type = NODE_BIN_EXPR;
	};
	
	// UNOP expr
	// eg. ++i
	class PreUnaryExprAST : public ExprAST {
	public:
		PreUnaryExprAST(std::unique_ptr<ExprAST> _expr, OPERATORS _op);
		
		std::shared_ptr<Fuse::Object> Eval();
	private:
		std::unique_ptr<ExprAST> Expr;
		OPERATORS Operator;
	
		TypeAST type = NODE_UNOP_EXPR;
	};
	
	// expr UNOP
	// eg. i++
	class PostUnaryExprAST : public ExprAST {
	public:
		PostUnaryExprAST(std::unique_ptr<ExprAST> _expr, OPERATORS _op);
		
		std::shared_ptr<Fuse::Object> Eval();
	private:
		std::unique_ptr<ExprAST> Expr;
		OPERATORS Operator;
	
		TypeAST type = NODE_UNOP_EXPR;
	};
	
}