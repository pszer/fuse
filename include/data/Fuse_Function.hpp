#pragma once

#include "ast/Base.hpp" // For FunctionAST

namespace Fuse {
	
	class Function : Object {
	public:
		Function() { ; }
		Function(FunctionAST* _func): Func(_func) { ; }
		
		Function* Clone();
		
		const std::vector<std::string>& GetArgs();
		const StatAST * GetBody();
		
		std::string ToString();
	private:
		Type type = TYPE_FUNCTION;
		FunctionAST * Func = nullptr;
	};
	
};