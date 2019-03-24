#pragma once

#include "ast/Base.hpp"

namespace Fuse {

	class IfElseAST : public ExprAST {
	public:
		// for an if statement without an else
		IfElseAST(std::unique_ptr<ExprAST> cond, std::unique_ptr<ExprAST> body);
		// for an if-else statement
		IfElseAST(std::unique_ptr<ExprAST> cond, std::unique_ptr<ExprAST> body,
			std::unique_ptr<ExprAST> else_body);
		
		std::shared_ptr<Fuse::Object> Eval();
		TypeAST GetType();
	private:
		std::unique_ptr<ExprAST> cond, body, else_body = nullptr;
	};
	
};