#pragma once

#include "ast/Base.hpp" // For FunctionAST

namespace Fuse {
	
	class Function : public Object {
	public:
		Function() { ; }
		Function(std::shared_ptr<FunctionAST> _func): Func(_func) { ; }
		
		Type GetType();
		
		Function* Clone();
		
		const std::vector<std::string>& GetArgs();
		std::string ToString();
		
		std::shared_ptr<Fuse::Object> Call(std::vector< std::shared_ptr<Object> >& call_args);
		bool IsTrue();
	private:
		std::shared_ptr<FunctionAST> Func = nullptr;
	};
	
};