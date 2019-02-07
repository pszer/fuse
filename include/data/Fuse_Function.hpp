#pragma once

#include "ast/Base.hpp" // For FunctionAST

namespace Fuse {
	
	class Function : Object {
	public:
		Function();
		Function(std::unique_ptr<FunctionAST> _func): func(std::move(_func)) { ; }
		
		Function* Clone(); // returns nullptr at the moment
		
		const std::string& GetName();
		const std::vector<std::string>& GetArgs();
		
		std::string ToString();
	private:
		Type type = TYPE_FUNCTION;
		std::unique_ptr<FunctionAST> func;
	};
	
};