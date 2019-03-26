#include "ast/Assign.hpp"

#include "ast/Variable.hpp"
#include "ast/TableAccess.hpp"
#include "Fuse_Core.hpp"

using namespace Fuse;

TypeAST Fuse::AssignAST::GetType() {
	return NODE_ASSIGN;
}

std::shared_ptr<Fuse::Object> Fuse::AssignAST::Eval() {
	auto RHS_Eval = RHS_Expr->Eval();
	if (RHS_Eval == nullptr) return nullptr;
	
	if (LHS_Expr->GetType() == NODE_VARIABLE) {
		return dynamic_cast<VariableAST*>(LHS_Expr.get())->Assign(RHS_Eval);
	} else if (LHS_Expr->GetType() == NODE_TABLE_ACCESS) {
		return dynamic_cast<TableAccessAST*>(LHS_Expr.get())->Assign(RHS_Eval);
	} else {
		return Core.SetErrorMessage("trying to assign a value to non-variable expression");
	}
}