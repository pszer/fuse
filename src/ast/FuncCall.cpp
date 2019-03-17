#include "ast/FuncCall.hpp"

using namespace Fuse;

Fuse::FuncCallAST::FuncCallAST(std::unique_ptr<ExprAST> _id, std::vector<std::unique_ptr<ExprAST>>& _args):
	Id(std::move(_id)), Args(std::move(_args))
{
	Args.shrink_to_fit();
}

std::shared_ptr<Fuse::Object> Fuse::FuncCallAST::Eval() {
	auto func = Id->Eval();
	if (func->GetType() == TYPE_FUNCTION) {
		std::vector<std::shared_ptr<Object>> CallArgs;
		for (auto arg = Args.begin(); arg != Args.end(); ++arg) {
			CallArgs.push_back((*arg)->Eval());
		}
		
		return dynamic_cast<Function*>(func.get())->Call(CallArgs);
	} else {
		return nullptr;
	}
}

TypeAST Fuse::FuncCallAST::GetType() {
	return NODE_FUNC_CALL;
}