#include "ast/BinaryExpr.hpp"

using namespace Fuse;

TypeAST Fuse::BinaryExprAST::GetType() {
	return NODE_BIN_EXPR;
}

std::shared_ptr<Fuse::Object> Fuse::BinaryExprAST::Eval() {
	std::cout << "BINARY OPERATION" << std::endl;
	auto LHS_OBJ = LHS->Eval(),
	     RHS_OBJ = RHS->Eval();
	if (LHS_OBJ == nullptr || RHS_OBJ == nullptr) std::cout << "whoops" << std::endl;
	return DoOperation(LHS_OBJ, RHS_OBJ, Operator);
}