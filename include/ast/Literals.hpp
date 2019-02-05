#pragma once

#include "ast/Base.hpp"

namespace Fuse {

	class NumberAST : ExprAST {
	public:
		std::shared_ptr<Fuse::Object> Eval();
	private:
		Fuse::INumber INum;
		TypeAST type = NODE_NUMBER;
	};
	
	class StringAST : ExprAST {
	public:
		std::shared_ptr<Fuse::Object> Eval();
	private:
		std::string String;
		TypeAST type = NODE_NUMBER;
	};
};