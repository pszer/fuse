#include "ast/Base.hpp"

using namespace Fuse;

TypeAST Fuse::StatAST::GetType() {
	return type;
}

TypeAST Fuse::ExprAST::GetType() {
	return type;
}

const std::string& Fuse::PrototypeAST::GetName() {
	return Name;
}

const std::vector<std::string>& Fuse::PrototypeAST::GetArgs() {
	return Args;
}

const std::string& Fuse::FunctionAST::GetName() {
	return Proto.GetName();
}

const std::vector<std::string>& Fuse::FunctionAST::GetArgs() {
	return Proto.GetArgs();
}