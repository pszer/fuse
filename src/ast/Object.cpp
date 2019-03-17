#include "ast/Object.hpp"

using namespace Fuse;

std::shared_ptr<Fuse::Object> ObjectAST::Eval() { return Obj; }
std::shared_ptr<Fuse::Object> ObjectAST::GetObject() { return Obj; }

TypeAST Fuse::ObjectAST::GetType() {
	return NODE_OBJECT;
}

Type ObjectAST::GetObjType() {
	return Obj->GetType();
}