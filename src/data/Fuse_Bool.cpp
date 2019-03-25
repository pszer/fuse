#include "data/Fuse_Bool.hpp"

using namespace Fuse;

Fuse::Bool::Bool() { ; }

Type Fuse::Bool::GetType() {
	return TYPE_BOOL;
}

std::shared_ptr<Object> Fuse::Bool::Clone() {
	return std::make_shared<Bool>(val);
}

bool& Fuse::Bool::Value() {
	return val;
}

std::string Fuse::Bool::ToString() {
	if (val) return "true";
	else return "false";
}

bool Fuse::Bool::IsTrue() {
	return val;
}