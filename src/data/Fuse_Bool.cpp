#include "data/Fuse_Bool.hpp"

using namespace Fuse;

Fuse::Bool::Bool() { ; }

Type Fuse::Bool::GetType() {
	return TYPE_BOOL;
}

Bool* Fuse::Bool::Clone() {
	auto n = new Bool();
	*n = *this;
	return n;
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