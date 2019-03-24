#pragma once

#include <utility>
#include <math.h>

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
	std::shared_ptr<Object> __Num_Num_Mod__(std::shared_ptr<Object> a,std::shared_ptr<Object> b);
	
	std::shared_ptr<Object> __Num_Num_Equal__(std::shared_ptr<Object> a,std::shared_ptr<Object> b);
	std::shared_ptr<Object> __Num_Num_Unequal__(std::shared_ptr<Object> a,std::shared_ptr<Object> b);
	std::shared_ptr<Object> __Num_Num_Less__(std::shared_ptr<Object> a,std::shared_ptr<Object> b);
	std::shared_ptr<Object> __Num_Num_Greater__(std::shared_ptr<Object> a,std::shared_ptr<Object> b);
	std::shared_ptr<Object> __Num_Num_EqLess__(std::shared_ptr<Object> a,std::shared_ptr<Object> b);
	std::shared_ptr<Object> __Num_Num_EqGreater__(std::shared_ptr<Object> a,std::shared_ptr<Object> b);
	std::shared_ptr<Object> __Num_Num_And__(std::shared_ptr<Object> a,std::shared_ptr<Object> b);
	std::shared_ptr<Object> __Num_Num_Or__(std::shared_ptr<Object> a,std::shared_ptr<Object> b);
	
	std::shared_ptr<Object> __Bool_Bool_Equal__(std::shared_ptr<Object> a,std::shared_ptr<Object> b);
	std::shared_ptr<Object> __Bool_Bool_Unequal__(std::shared_ptr<Object> a,std::shared_ptr<Object> b);
	std::shared_ptr<Object> __Bool_Bool_And__(std::shared_ptr<Object> a,std::shared_ptr<Object> b);
	std::shared_ptr<Object> __Bool_Bool_Or__(std::shared_ptr<Object> a,std::shared_ptr<Object> b);
	
	std::shared_ptr<Object> __Str_Str_Equal__(std::shared_ptr<Object> a,std::shared_ptr<Object> b);
	std::shared_ptr<Object> __Str_Str_Unequal__(std::shared_ptr<Object> a,std::shared_ptr<Object> b);
	std::shared_ptr<Object> __Str_Str_Add__(std::shared_ptr<Object> a,std::shared_ptr<Object> b);
	std::shared_ptr<Object> __Str_Num_Add__(std::shared_ptr<Object> a,std::shared_ptr<Object> b);
	std::shared_ptr<Object> __Num_Str_Add__(std::shared_ptr<Object> a,std::shared_ptr<Object> b);
	std::shared_ptr<Object> __Str_Bool_Add__(std::shared_ptr<Object> a,std::shared_ptr<Object> b);
	std::shared_ptr<Object> __Bool_Str_Add__(std::shared_ptr<Object> a,std::shared_ptr<Object> b);
}
