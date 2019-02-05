#include "data/Fuse_Number.hpp"

using namespace Fuse;

Fuse::Number::Number() { ; }

Number* Fuse::Number::Clone() {
	auto n = new Number();
	*n = *this;
	return n;
}

INumber& Fuse::Number::GetNum() {
	return val;
}

std::string Fuse::Number::ToString() {
	if (val.type == INT)
		return std::to_string(val.INT);
	else return std::to_string(val.DOUBLE);
}