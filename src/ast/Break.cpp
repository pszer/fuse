#include "ast/Break.hpp"

using namespace Fuse;

std::shared_ptr<Fuse::Object> BreakAST::Eval() {
	return std::make_shared<Signal>(SIG_BREAK);
}

TypeAST BreakAST::GetType() {
	return NODE_BREAK;
}

std::shared_ptr<Fuse::Object> ContinueAST::Eval() {
	return std::make_shared<Signal>(SIG_CONTINUE);
}

TypeAST ContinueAST::GetType() {
	return NODE_CONTINUE;
}