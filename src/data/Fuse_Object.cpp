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

std::shared_ptr<Object> Fuse::Object::Clone() {
	return nullptr;
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


std::shared_ptr<Object> Null::Clone() {
	return std::make_shared<Null>();
}

std::string Null::ToString() {
	return "null";
}

bool Fuse::Null::IsTrue() {
	return false;
}

std::shared_ptr<Object> Fuse::Signal::Clone() { return std::make_shared<Signal>(SIGNAL); }
std::string Fuse::Signal::ToString() { return ""; }
Type Fuse::Signal::GetType() { return TYPE_SIGNAL; }
bool Fuse::Signal::IsTrue() { return false; }