#include "ast/Variable.hpp"

#include "Fuse_Core.hpp"

using namespace Fuse;

TypeAST Fuse::VariableAST::GetType() {
	return NODE_VARIABLE;
}

std::shared_ptr<Fuse::Object> VariableAST::Eval() {
	auto v = Fuse::Core.GetVariable(Identifier);
	if (v == nullptr) return nullptr;
	
	return *v;
}

std::shared_ptr<Fuse::Object>* VariableAST::Assign() {
	auto v = Fuse::Core.GetVariable(Identifier);
	if (v) return v;
	
	v = Fuse::Core.CreateVariable(Identifier, nullptr);
	return v;
}

const std::string& VariableAST::GetIdentifier() {
	return Identifier;
}
