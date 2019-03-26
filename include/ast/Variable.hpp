#pragma once

#include "ast/Base.hpp"

using VariableScopes = std::vector< std::map<std::string, std::shared_ptr<Fuse::Object>> >;

namespace Fuse {

	class Core;

	class VariableAST : public ExprAST {
	public:
		VariableAST(std::string _id): Identifier(_id) { ; }
		
		TypeAST GetType();
		
		// Returns nullptr for an error
		std::shared_ptr<Fuse::Object> Eval();
		std::shared_ptr<Fuse::Object> Assign(std::shared_ptr<Object> obj);
		
		const std::string& GetIdentifier();
	private:
		std::string Identifier;
		
		TypeAST type = NODE_VARIABLE;
	};

};