#pragma once

#include "ast/Base.hpp"

namespace Fuse {

	/* Used for standard function definitions such as
		function foo(x,y) return x+y;
		^ FuncDefStatAST
	*/
	class FuncDefStatAST : public StatAST {
	public:
		FuncDefStatAST(std::shared_ptr<FunctionAST> _func): Func(_func) { ; }
		
		std::shared_ptr<Fuse::Object> Eval();
		std::shared_ptr<FunctionAST> GetFunc();
	private:
		std::shared_ptr<FunctionAST> Func = nullptr;
		TypeAST type = NODE_FUNC_DEF;
	};

	/* Used for anonymous function definitions such as
		foo = function(x,y) return x+y;
		      ^ FuncDefExprAST
	*/
	class FuncDefExprAST : public ExprAST {
	public:
		FuncDefExprAST(std::shared_ptr<FunctionAST> _func): Func(_func) { ; }
		
		std::shared_ptr<Fuse::Object> Eval();
		std::shared_ptr<FunctionAST> GetFunc();
	private:
		std::shared_ptr<FunctionAST> Func = nullptr;
		TypeAST type = NODE_FUNC_DEF;
	};

};