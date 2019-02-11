#include "Fuse_Core.hpp"

using namespace Fuse;

Core::Core(): _Parser( Parser(&_Lexer, &Scopes)) {
	Scopes.emplace_back(); // Create global scope
}

Scope& Core::GlobalScope() {
	return Scopes.front();
}

void Core::EnterScope() {
	Scopes.emplace_back();
}

void Core::LeaveScope() {
	// Never leave global scope
	if (Scopes.size() > 1) {
		Scopes.pop_back();
	}
}

std::shared_ptr<Fuse::Object>* Core::GetVariable(const std::string& var_name) {
	for (size_t i{ Scopes.size() }; --i;) {
		auto scope = Scopes.at(i);
		auto v = scope.find(var_name);
		if (v != scope.end()) return &(v->second);
	}
	
	return nullptr;
}

VAR_SET_STATE Core::SetVariable(const std::string& var_name, std::shared_ptr<Fuse::Object> obj) {
	auto var = GetVariable(var_name);
	
	if (var == nullptr) return ERROR;
	else *var = obj;
	return SUCCESS;
}

FunctionAST* Core::EmplaceFunction(const std::vector<std::string>& _args, std::unique_ptr<StatAST> _body) {
	Functions.emplace_back(_args, _body);
	return Functions.back().get();
}