#include "ast/Block.hpp"

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

std::shared_ptr<Fuse::Object> Fuse::BlockAST::Eval() {
	for (auto STAT = Statements.begin(); STAT != Statements.end(); ++STAT) { 
		// If return statement
		if (  (*STAT)->GetType() == NODE_RETURN ) {
			return (*STAT)->Eval();
		}
		
		(*STAT)->Eval();
	}
	
	return nullptr;
}

/*
ReturnAST
*/

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
		return std::shared_ptr<Object>((Object*) new Fuse::Null());
	} else {
		return Expr->Eval();
	}
}