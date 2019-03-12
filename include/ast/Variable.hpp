#pragma once

#include "ast/Base.hpp"

using VariableScopes = std::vector< std::map<std::string, std::shared_ptr<Fuse::Object>> >;

namespace Fuse {

	class Core;

	class VariableAST : public ExprAST {
	public:
		VariableAST(std::string _id): Identifier(_id) { ; }
		
		// Returns nullptr for an error
		std::shared_ptr<Fuse::Object> Eval();
		
		const std::string& GetIdentifier();
	private:
		std::string Identifier;
		
		TypeAST type = NODE_VARIABLE;
	};

};