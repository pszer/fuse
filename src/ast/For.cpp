#include "ast/For.hpp"

using namespace Fuse;

std::shared_ptr<Fuse::Object> Fuse::ForAST::Eval() {
	if (assign != nullptr)
		assign->Eval();
	
	while (1) {
		if (cond != nullptr) {
			auto cond_eval = cond->Eval();
			if (cond_eval == nullptr || !cond_eval->IsTrue()) return nullptr;
		}
		
		std::shared_ptr<Object> obj;
		if (body != nullptr) {
			obj = body->Eval();
			if (obj != nullptr && obj->GetType() == TYPE_SIGNAL) {
				auto sig = dynamic_cast<Signal*>(obj.get());
				if (sig->SIGNAL == SIG_BREAK) {
					return nullptr;
				} else if (sig->SIGNAL == SIG_CONTINUE) { ; }
			}
		}
			
		if (step != nullptr)
			step->Eval();
	}
	
	return nullptr;
}

TypeAST Fuse::ForAST::GetType() {
	return NODE_FOR;
}