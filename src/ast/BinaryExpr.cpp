#include "ast/BinaryExpr.hpp"

using namespace Fuse;

TypeAST Fuse::BinaryExprAST::GetType() {
	return NODE_BIN_EXPR;
}

std::shared_ptr<Fuse::Object> Fuse::BinaryExprAST::Eval() {
	auto LHS_OBJ = LHS->Eval(),
	     RHS_OBJ = RHS->Eval();
	
	if (LHS_OBJ == nullptr || RHS_OBJ == nullptr)
		return nullptr;
	return DoOperation(LHS_OBJ, RHS_OBJ, Operator);
}