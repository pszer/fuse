#include "ast/FuncDef.hpp"

using namespace Fuse;

TypeAST Fuse::FuncDefStatAST::GetType() {
	return NODE_FUNC_DEF;
}

TypeAST Fuse::FuncDefExprAST::GetType() {
	return NODE_FUNC_DEF;
}

std::shared_ptr<Fuse::Object> FuncDefStatAST::Eval() {
	return std::shared_ptr<Fuse::Object>( new Fuse::Function(Func) );
}

std::shared_ptr<Fuse::Object> FuncDefExprAST::Eval() {
	return std::shared_ptr<Fuse::Object>( new Fuse::Function(Func) );
}

std::shared_ptr<FunctionAST> FuncDefStatAST::GetFunc() {
	return Func;
}

std::shared_ptr<FunctionAST> FuncDefExprAST::GetFunc() {
	return Func;
}