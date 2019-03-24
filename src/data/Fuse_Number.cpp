#include "data/Fuse_Number.hpp"

using namespace Fuse;

Fuse::Number::Number() { ; }

Type Fuse::Number::GetType() {
	return TYPE_NUMBER;
}

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

bool Fuse::Number::IsTrue() {
	if (val.type == INT)
		return val.INT;
	return val.DOUBLE;
}