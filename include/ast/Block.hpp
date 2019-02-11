#pragma once

#include <vector>
#include <array>

#include "ast/Base.hpp"

namespace Fuse {

	class BlockAST : public StatAST {
	public:
		BlockAST(std::vector<std::unique_ptr<StatAST> >& _stats);
	
		// Eval returns something if there is a return statement
		// inside the block, otherwise it returns nullptr
		std::shared_ptr<Fuse::Object> Eval();
	private:
		std::vector<std::unique_ptr<StatAST> > Statements;
		TypeAST type = NODE_BLOCK;
	};

	class ReturnAST : public StatAST {
	public:
		// _expr can be nullptr, if it is then it
		// is an empty return statement that implicitly
		// returns a Fuse::Null object.
		ReturnAST(std::unique_ptr<ExprAST>& _expr);
		
		std::shared_ptr<Fuse::Object> Eval();
	private:
		std::unique_ptr<ExprAST> Expr;
		TypeAST type = NODE_RETURN;
	};
	
};