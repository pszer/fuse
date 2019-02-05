#include "data/Fuse_String.hpp"

using namespace Fuse;

Fuse::String::String() { ; }

String* Fuse::String::Clone() {
	auto n = new String();
	*n = *this;
	return n;
}

std::string& Fuse::String::Str() {
	return str;
}

std::string Fuse::String::ToString() {
	return str;
}