#include "ast/While.hpp"

using namespace Fuse;

std::shared_ptr<Fuse::Object> Fuse::WhileAST::Eval() {
	while (1) {
		auto cond_eval = cond->Eval();
		if (cond_eval == nullptr || !cond_eval->IsTrue()) return nullptr;
		
		body->Eval();
	}
}

TypeAST Fuse::WhileAST::GetType() {
	return NODE_WHILE;
}