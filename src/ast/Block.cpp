#include "ast/Block.hpp"
#include "Fuse_Core.hpp"

using namespace Fuse;

/*
BlockAST
*/

Fuse::BlockAST::BlockAST(std::vector<std::unique_ptr<ExprAST> >& _stats):
	Statements(std::move(_stats))
{
	// conserve space since more statements will never be added
	Statements.shrink_to_fit(); 
}

TypeAST Fuse::BlockAST::GetType() {
	return NODE_BLOCK;
}

std::shared_ptr<Fuse::Object> Fuse::BlockAST::Eval() {
	for (auto STAT = Statements.begin(); STAT != Statements.end(); ++STAT) { 
		// If return statement
		if ((*STAT)->GetType() == NODE_RETURN) {
			return (*STAT)->Eval();
		}
		
		auto eval = (*STAT)->Eval();
		if (eval == nullptr) return nullptr;
		if (eval->GetType() == TYPE_SIGNAL) {
			return eval;
		}
	}
	
	return NullReturn();
}

/*
ReturnAST
*/

TypeAST Fuse::ReturnAST::GetType() {
	return NODE_RETURN;
}

Fuse::ReturnAST::ReturnAST(std::unique_ptr<ExprAST>& _expr) {
	if (_expr == nullptr) {
		Expr = nullptr;
	} else {
		Expr = std::move(_expr);
	}
}

std::shared_ptr<Fuse::Object> Fuse::ReturnAST::Eval() {
	// If empty return statement
	if (Expr == nullptr) {
		// return implicit null
		return std::make_shared<Null>();;
	} else {
		return Expr->Eval();
	}
}