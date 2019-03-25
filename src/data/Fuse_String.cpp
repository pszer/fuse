#include "data/Fuse_String.hpp"

using namespace Fuse;

Fuse::String::String() { ; }

Type Fuse::String::GetType() {
	return TYPE_STRING;
}

std::shared_ptr<Object> Fuse::String::Clone() {
	return std::make_shared<String>(str);
}

std::string& Fuse::String::Str() {
	return str;
}

std::string Fuse::String::ToString() {
	return str;
}

bool Fuse::String::IsTrue() {
	return !str.empty();
}