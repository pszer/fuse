#include "ast/BinaryExpr.hpp"

using namespace Fuse;

std::shared_ptr<Fuse::Object> Fuse::BinaryExprAST::Eval() {
	return DoOperation(LHS->Eval(), RHS->Eval(), Operator);
}