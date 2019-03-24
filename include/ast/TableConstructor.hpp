#pragma once

#include "ast/Base.hpp"

namespace Fuse {

	struct TableConstructEntry {
		TableConstructEntry(std::unique_ptr<ExprAST> _key, std::unique_ptr<ExprAST> _expr):
			key(std::move(_key)), expr(std::move(_expr)) { ; }
		TableConstructEntry(std::unique_ptr<ExprAST> _expr):
			expr(std::move(_expr)) { ; }
			
		std::unique_ptr<ExprAST> key = nullptr, expr;
	};

	class TableConstructorAST : public ExprAST {
	public:
		TableConstructorAST(std::vector<TableConstructEntry> & _table): entries(std::move(_table)) { ; }
		
		std::shared_ptr<Fuse::Object> Eval();
		TypeAST GetType();
	private:
		std::vector<TableConstructEntry> entries;
	};

};