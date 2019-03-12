#pragma once

#include <map>

#include "data/Fuse_Object.hpp"
#include "Lexer.hpp"

namespace Fuse {
	
	unsigned int OpDef (Type _LHS, Type _RHS, OPERATORS _Op);
	
	typedef std::shared_ptr<Object> (*Operation_Func)(std::shared_ptr<Object>,std::shared_ptr<Object>);
	extern std::map< unsigned int, Operation_Func> Operations;
	void InitOperations();
		
	Operation_Func GetOperation(Type a, Type b, OPERATORS op);
	
	// nullptr if no operation can be found
	std::shared_ptr<Object> DoOperation(std::shared_ptr<Object> a, std::shared_ptr<Object> b, OPERATORS op);
	
	std::shared_ptr<Object> __Num_Num_Add__(std::shared_ptr<Object> a,std::shared_ptr<Object> b);
	std::shared_ptr<Object> __Num_Num_Sub__(std::shared_ptr<Object> a,std::shared_ptr<Object> b);
}