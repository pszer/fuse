#pragma once

#include "ast/Base.hpp"

namespace Fuse {
	
	class TableAccessAST : public ExprAST {
	public:
		TableAccessAST(std::unique_ptr<ExprAST> _table, std::unique_ptr<ExprAST> _access):
			table(std::move(_table)), access(std::move(_access)) { ; }
			
		std::shared_ptr<Fuse::Object> Eval();
		TypeAST GetType();
		std::shared_ptr<Fuse::Object>* Assign();
	private:
		std::unique_ptr<ExprAST> table, access;
	};
	
};