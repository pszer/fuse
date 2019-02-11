#include "ast/Object.hpp"

using namespace Fuse;

std::shared_ptr<Fuse::Object> ObjectAST::Eval() { return Obj; }
std::shared_ptr<Fuse::Object> ObjectAST::GetObject() { return Obj; }

Type ObjectAST::GetObjType() {
	return Obj->GetType();
}