#pragma once

#include "ast/Base.hpp"

using VariableScopes = std::vector< std::map<std::string, std::shared_ptr<Fuse::Object>> >;

namespace Fuse {

	class VariableAST : ExprAST {
	public:
		VariableAST(std::string _id, VariableScopes * _loc): Identifier(_id) { ; }
		
		// Returns nullptr for an error
		std::shared_ptr<Fuse::Object> Eval();
		
		const std::string& GetIdentifier();
	private:
		std::string Identifier;
		VariableScopes * Locations;
		
		TypeAST type = NODE_VARIABLE;
	};

};