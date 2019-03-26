#include "ast/BinaryExpr.hpp"
#include "Fuse_Core.hpp"

using namespace Fuse;

TypeAST Fuse::BinaryExprAST::GetType() {
	return NODE_BIN_EXPR;
}

std::shared_ptr<Fuse::Object> Fuse::BinaryExprAST::Eval() {
	auto LHS_OBJ = LHS->Eval(),
	     RHS_OBJ = RHS->Eval();
	
	if (LHS_OBJ == nullptr || RHS_OBJ == nullptr)
		return nullptr;
	auto result = DoOperation(LHS_OBJ, RHS_OBJ, Operator);
	if (result == nullptr) {
		return Core.SetErrorMessage("unknown operation \'" + op_str[Operator] + "\' between data types \"" +
			TypeName[LHS_OBJ->GetType()] + "\" and \"" + TypeName[RHS_OBJ->GetType()] + "\"");
	}
	
	return result;
}