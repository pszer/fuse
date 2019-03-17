#pragma once

#include <utility>

#include "data/Fuse_Object.hpp"
#include "Lexer.hpp"

namespace Fuse {
	
	typedef std::shared_ptr<Object> (*Operation_Func)(std::shared_ptr<Object>,std::shared_ptr<Object>);
	
	struct Operation {
		Operation(Type _a, Type _b, Operation_Func _func):
			a(_a), b(_b), func(_func) { ; }
		
		Type a, b;
		Operation_Func func;
	};
	
	void InitOperations();
		
	Operation_Func GetOperation(Type a, Type b, OPERATORS op);
	
	// nullptr if no operation can be found
	std::shared_ptr<Object> DoOperation(std::shared_ptr<Object> a, std::shared_ptr<Object> b, OPERATORS op);
	
	std::shared_ptr<Object> __Num_Num_Add__(std::shared_ptr<Object> a,std::shared_ptr<Object> b);
	std::shared_ptr<Object> __Num_Num_Sub__(std::shared_ptr<Object> a,std::shared_ptr<Object> b);
	std::shared_ptr<Object> __Num_Num_Mult__(std::shared_ptr<Object> a,std::shared_ptr<Object> b);
	std::shared_ptr<Object> __Num_Num_Div__(std::shared_ptr<Object> a,std::shared_ptr<Object> b);
	
}
