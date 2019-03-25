#include "ast/Base.hpp"
#include "Fuse_Core.hpp"

using namespace Fuse;

const std::vector<std::string>& FunctionAST::GetArgs() {
	return Args;
}

const ExprAST * FunctionAST::GetBody() {
	return Body.get();
}

bool FunctionAST::IsCFunc() {
	return CFunc != nullptr;
}

std::shared_ptr<Fuse::Object> FunctionAST::Call(std::vector< std::shared_ptr<Object> >& call_args) {
	if (!IsCFunc())
		return CallFuseFunc(call_args);
	else
		return CallCFunc(call_args);
}

std::shared_ptr<Fuse::Object> FunctionAST::CallFuseFunc(std::vector< std::shared_ptr<Object> >& call_args) {
	if (Args.size() != call_args.size()) {
		return nullptr;
	}
	
	std::shared_ptr<std::vector<Scope>> new_scope = std::make_shared<std::vector<Scope>>();
	new_scope->emplace_back();
	
	for (int i = 0; i < Args.size(); ++i) {
		new_scope->back()[Args.at(i)] = call_args.at(i);
	}
	
	auto old_scope = Core.EnterScope(new_scope);
	
	if (Body == nullptr) return nullptr;
	auto body_eval = Body->Eval();
	
	Core.EnterScope(old_scope);
	
	return std::move(body_eval);
}

std::shared_ptr<Fuse::Object> FunctionAST::CallCFunc(std::vector< std::shared_ptr<Object> >& call_args) {
	if (CFuncArgTypes.size() != call_args.size()) {
		return nullptr;
	}
	
	for (int i = 0; i < CFuncArgTypes.size(); ++i) {
		if (CFuncArgTypes.at(i) == TYPE_OBJECT) continue;
		
		auto type = call_args.at(i)->GetType();
		if (type != CFuncArgTypes.at(i)) {
			return nullptr;
		}
	}
	
	return CFunc(call_args);
}

std::shared_ptr<Object> Fuse::VoidAST::Eval() {
	return nullptr;
}

TypeAST Fuse::VoidAST::GetType() {
	return NODE_NULL;
}