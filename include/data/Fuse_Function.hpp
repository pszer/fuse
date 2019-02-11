#pragma once

#include "ast/Base.hpp" // For FunctionAST

namespace Fuse {
	
	class Function : public Object {
	public:
		Function() { ; }
		Function(std::shared_ptr<FunctionAST> _func): Func(_func) { ; }
		
		Function* Clone();
		
		const std::vector<std::string>& GetArgs();
		const StatAST * GetBody();
		
		std::string ToString();
	private:
		Type type = TYPE_FUNCTION;
		std::shared_ptr<FunctionAST> Func = nullptr;
	};
	
};