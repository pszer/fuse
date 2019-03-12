#include "Fuse_Core.hpp"

using namespace Fuse;

struct Fuse::Core Fuse::Core;

Core::Core(): _Parser( Parser(&_Lexer, &Scopes)) {
	InitOperations();
}

std::unique_ptr<ExprAST> Core::Parse() {
	return std::move(_Parser.Parse());
}

Scope& Core::TopScope() {
	if (Scopes.empty())
		return GlobalScope;
	else 
		return Scopes.back();
}

void Core::EnterScope() {
	Scopes.emplace_back();
}

void Core::LeaveScope() {
	if (Scopes.size() > 0) {
		Scopes.pop_back();
	}
}

std::shared_ptr<Fuse::Object>* Core::GetVariable(const std::string& var_name) {
	for (size_t i{ Scopes.size() }; --i;) {
		auto scope = Scopes.at(i);
		auto v = scope.find(var_name);
		if (v != scope.end()) return &(v->second);
	}
	
	auto v = GlobalScope.find(var_name);
	if (v != GlobalScope.end()) return &(v->second);
	
	return nullptr;
}

VAR_SET_STATE Core::SetVariable(const std::string& var_name, std::shared_ptr<Fuse::Object> obj) {
	auto var = GetVariable(var_name);
	
	if (var == nullptr) return ERROR;
	else *var = obj;
	return SUCCESS;
}

void Core::CreateVariable(const std::string& var_name, std::shared_ptr<Fuse::Object> obj) {
	if (!Scopes.empty())
		Scopes.back()[var_name] = obj;
	else
		GlobalScope[var_name] = obj;
	
}