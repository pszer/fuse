#include "data/Fuse_Object.hpp"

#include "data/Fuse_Table.hpp"
#include "data/Fuse_Number.hpp"
#include "data/Fuse_String.hpp"
#include "data/Fuse_Bool.hpp"
#include "data/Fuse_Function.hpp"

using namespace Fuse;

Type Fuse::Object::GetType() {
	return TYPE_OBJECT;
}

Object* Fuse::Object::Clone() {
	
}

std::string Fuse::Object::ToString() {
	return "";
}

bool Fuse::Object::IsTrue() {
	return false;
}

// null

Type Fuse::Null::GetType() {
	return TYPE_NULL;
}


Null* Null::Clone() {
	auto n = new Null();
	*n = *this;
	return n;
}

std::string Null::ToString() {
	return "null";
}

bool Fuse::Null::IsTrue() {
	return false;
}