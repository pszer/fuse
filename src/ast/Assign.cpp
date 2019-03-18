#include "ast/Assign.hpp"

#include "ast/Variable.hpp"

using namespace Fuse;

TypeAST Fuse::AssignAST::GetType() {
	return NODE_ASSIGN;
}

std::shared_ptr<Fuse::Object> Fuse::AssignAST::Eval() {
	std::shared_ptr<Object>* LHS = nullptr;
	if (LHS_Expr->GetType() == NODE_VARIABLE) {
		LHS = dynamic_cast<VariableAST*>(LHS_Expr.get())->Assign();
	} else return nullptr;
	
	*LHS = RHS_Expr->Eval();
	return *LHS;
}