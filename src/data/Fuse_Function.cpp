#include "data/Fuse_Function.hpp"

using namespace Fuse;

Function* Fuse::Function::Clone() {
	auto n = new Function();
	*n = *this;
	return n;
}

std::string Fuse::Function::ToString() {
	return "function address: " + std::to_string((int)Func->GetBody());
}

const std::vector<std::string>& Fuse::Function::GetArgs() {
	return Func->GetArgs();
}

const StatAST * Fuse::Function::GetBody() {
	return Func->GetBody();
}