#include "ast/FuncCall.hpp"
#include "Fuse_Core.hpp"

using namespace Fuse;

Fuse::FuncCallAST::FuncCallAST(std::unique_ptr<ExprAST> _id, std::vector<std::unique_ptr<ExprAST>>& _args):
	Id(std::move(_id)), Args(std::move(_args))
{
	Args.shrink_to_fit();
}

std::shared_ptr<Fuse::Object> Fuse::FuncCallAST::Eval() {
	auto func = Id->Eval();
	if (func == nullptr) return nullptr;
	
	if (func->GetType() == TYPE_FUNCTION) {
		std::vector<std::shared_ptr<Object>> CallArgs;
		for (auto arg = Args.begin(); arg != Args.end(); ++arg) {
			CallArgs.push_back((*arg)->Eval());
		}
		
		auto f = dynamic_cast<Function*>(func.get());
		if (f == nullptr) {
			return Core.SetErrorMessage("error getting function in function call");
		}
		return f->Call(CallArgs);
	} else {
		Core.SetErrorMessage("trying to call non-function object");
		return nullptr;
	}
}

TypeAST Fuse::FuncCallAST::GetType() {
	return NODE_FUNC_CALL;
}