#pragma once

#include "ast/Base.hpp"

namespace Fuse {

	class FuncCallAST : public ExprAST {
	public:
		FuncCallAST(std::unique_ptr<ExprAST> _id, std::vector<std::unique_ptr<ExprAST>>& _args);
		
		std::shared_ptr<Fuse::Object> Eval();
		TypeAST GetType();
	private:
		std::unique_ptr<ExprAST> Id;
		std::vector< std::unique_ptr<ExprAST> > Args;
	};
	
};