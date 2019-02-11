#include "ast/FuncDef.hpp"

using namespace Fuse;

std::shared_ptr<Fuse::Object> FuncDefStatAST::Eval() {
	return std::shared_ptr<Fuse::Object>( (Object*)new Fuse::Function(Func) );
}

std::shared_ptr<Fuse::Object> FuncDefExprAST::Eval() {
	return std::shared_ptr<Fuse::Object>( (Object*)new Fuse::Function(Func) );
}

std::shared_ptr<FunctionAST> FuncDefStatAST::GetFunc() {
	return Func;
}

std::shared_ptr<FunctionAST> FuncDefExprAST::GetFunc() {
	return Func;
}