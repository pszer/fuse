#include "ast/IfElse.hpp"
#include "Fuse_Core.hpp"

using namespace Fuse;

Fuse::IfElseAST::IfElseAST(std::unique_ptr<ExprAST> _cond, std::unique_ptr<ExprAST> _body):
  cond(std::move(_cond)), body(std::move(_body)), else_body(nullptr) { ; }
  
Fuse::IfElseAST::IfElseAST(std::unique_ptr<ExprAST> _cond, std::unique_ptr<ExprAST> _body,
			std::unique_ptr<ExprAST> _else_body):
  cond(std::move(_cond)), body(std::move(_body)), else_body(std::move(_else_body)) { ; }
  
TypeAST Fuse::IfElseAST::GetType() {
	return NODE_IF_ELSE;
}

std::shared_ptr<Fuse::Object> Fuse::IfElseAST::Eval() {
	auto cond_eval = cond->Eval();
	if (cond_eval == nullptr) return nullptr;
	
	if (cond_eval->IsTrue()) {
		return body->Eval();
	} else {
		if (else_body != nullptr)
			return else_body->Eval();
		return NullReturn();
	}
}