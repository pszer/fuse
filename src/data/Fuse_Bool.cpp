#include "data/Fuse_Bool.hpp"

using namespace Fuse;

Fuse::Bool::Bool() { ; }

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