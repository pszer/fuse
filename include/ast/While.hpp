#pragma once

#include "ast/Base.hpp"

namespace Fuse {

	class WhileAST : public ExprAST {
	public:
		WhileAST(std::unique_ptr<ExprAST> _cond, std::unique_ptr<ExprAST> _body):
		  cond(std::move(_cond)), body(std::move(_body)) { ; }
		  
		std::shared_ptr<Fuse::Object> Eval();
		TypeAST GetType();
	private:
		std::unique_ptr<ExprAST> cond, body;
	};

};