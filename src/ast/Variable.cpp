#include "ast/Variable.hpp"

using namespace Fuse;

std::shared_ptr<Fuse::Object> VariableAST::Eval() {
	for (size_t i{ Locations->size() }; --i;) {
		auto scope = Locations->at(i);
		auto v = scope.find(Identifier);
		if (v != scope.end()) return v->second;
	}
	
	return nullptr;
}

const std::string& VariableAST::GetIdentifier() {
	return Identifier;
}