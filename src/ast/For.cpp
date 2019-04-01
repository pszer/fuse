#include "ast/For.hpp"
#include "Fuse_Core.hpp"

using namespace Fuse;

TypeAST Fuse::ForAST::GetType() {
	return NODE_FOR;
}

std::shared_ptr<Fuse::Object> Fuse::ForAST::Eval() {
	if (assign != nullptr)
		assign->Eval();
	
	while (1) {	
		if (cond != nullptr) {
			auto cond_eval = cond->Eval();
			if (cond_eval == nullptr || !cond_eval->IsTrue()) break;
		}
		
		std::shared_ptr<Object> obj;
		if (body != nullptr) {
			obj = body->Eval();
			if (obj == nullptr) return nullptr;
			
			if (obj->GetType() == TYPE_SIGNAL) {
				auto sig = dynamic_cast<Signal*>(obj.get());
				if (sig->SIGNAL == SIG_BREAK) {
					return std::make_shared<Null>();
				} else if (sig->SIGNAL == SIG_CONTINUE) { ; }
			}
		}
		
		if (step != nullptr) {
			if (step->Eval() == nullptr) return nullptr;
		}
	}
	
	return NullReturn();
}

TypeAST Fuse::ForTableAST::GetType() {
	return NODE_FOR;
}

std::shared_ptr<Fuse::Object> Fuse::ForTableAST::Eval() {
	if (table == nullptr) return nullptr;
	auto table_eval = table->Eval();
	if (table_eval == nullptr) return nullptr;
	if (table_eval->GetType() != TYPE_TABLE) {
		Core.SetErrorMessage("trying to iterate through a non-table object");
		return nullptr;
	}
	
	auto table = GetTable(table_eval);
	for (std::size_t i = 0; i < table->Count(); ++i) {
		Core.CreateVariable(var_name, table->Access(i));
		
		if (body != nullptr) {
			auto obj = body->Eval();
			if (obj == nullptr) return nullptr;
			
			if (obj->GetType() == TYPE_SIGNAL) {
				auto sig = dynamic_cast<Signal*>(obj.get());
				if (sig->SIGNAL == SIG_BREAK) {
					return std::make_shared<Null>();
				} else if (sig->SIGNAL == SIG_CONTINUE) { ; }
			}
		}
	}
	
	return NullReturn();
}