#include "ast/While.hpp"
#include "Fuse_Core.hpp"

using namespace Fuse;

std::shared_ptr<Fuse::Object> Fuse::WhileAST::Eval() {
	while (1) {
		auto cond_eval = cond->Eval();
		if (cond_eval == nullptr || !cond_eval->IsTrue()) return nullptr;
		
		auto obj = ScopedEval(body);
		if (obj == nullptr) return nullptr;
		
		if (obj->GetType() == TYPE_SIGNAL) {
			auto sig = dynamic_cast<Signal*>(obj.get());
			if (sig->SIGNAL == SIG_BREAK) {
				return std::make_shared<Null>();
			} else if (sig->SIGNAL == SIG_CONTINUE) { ; }
		}
	}
	
	return NullReturn();
}

TypeAST Fuse::WhileAST::GetType() {
	return NODE_WHILE;
}