#pragma once

#include "ast/Base.hpp"

namespace Fuse {

	/* Used for standard function definitions such as
		function foo(x,y) return x+y;
		^ FuncDefStatAST
	*/
	class FuncDefStatAST : StatAST {
	public:
		FuncDefStatAST(FunctionAST* _func): Func(_func) { ; }
		
		std::shared_ptr<Fuse::Object> Eval();
	private:
		FunctionAST* Func = nullptr;
		TypeAST type = NODE_FUNC_DEF;
	};

	/* Used for anonymous function definitions such as
		foo = function(x,y) return x+y;
		      ^ FuncDefExprAST
	*/
	class FuncDefExprAST : ExprAST {
	public:
		FuncDefExprAST(FunctionAST* _func): Func(_func) { ; }
		
		std::shared_ptr<Fuse::Object> Eval();
	private:
		FunctionAST* Func = nullptr;
		TypeAST type = NODE_FUNC_DEF;
	};

};