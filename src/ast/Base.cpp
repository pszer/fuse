#include "ast/Base.hpp"

using namespace Fuse;

TypeAST Fuse::StatAST::GetType() {
	return type;
}

TypeAST Fuse::ExprAST::GetType() {
	return type;
}


const std::vector<std::string>& FunctionAST::GetArgs() {
	return Args;
}

const StatAST * FunctionAST::GetBody() {
	return Body.get();
}

std::shared_ptr<Fuse::Object> FunctionAST::Call() {
	std::cout << "Function at address : " << (std::size_t)Body.get() << " was called" << std::endl;
}