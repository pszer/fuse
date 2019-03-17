#include "ast/Base.hpp"
#include "Fuse_Core.hpp"

using namespace Fuse;

const std::vector<std::string>& FunctionAST::GetArgs() {
	return Args;
}

const ExprAST * FunctionAST::GetBody() {
	return Body.get();
}

std::shared_ptr<Fuse::Object> FunctionAST::Call(std::vector< std::shared_ptr<Object> >& call_args) {
	std::cout << "Function at address : " << (std::size_t)Body.get() << " was called" << std::endl;
	if (Args.size() != call_args.size()) {
		std::cout << "Invalid amount of arguments" << std::endl;
		return nullptr;
	}
	
	for (int i = 0; i < Args.size(); ++i) {
		Core.CreateVariable(Args.at(i), call_args.at(i));
	}
	
	if (Body == nullptr) return nullptr;
	return Body->Eval();
}