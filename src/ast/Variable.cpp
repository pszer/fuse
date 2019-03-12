#include "ast/Variable.hpp"

#include "Fuse_Core.hpp"

using namespace Fuse;

std::shared_ptr<Fuse::Object> VariableAST::Eval() {
	auto v = Fuse::Core.GetVariable(Identifier);
	
	return nullptr;
}

const std::string& VariableAST::GetIdentifier() {
	return Identifier;
}