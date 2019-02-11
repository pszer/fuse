#include "data/Fuse_Object.hpp"

using namespace Fuse;

Object* Fuse::Clone(Object* o) {
	switch (o->GetType()) {
	case TYPE_NUMBER:
		return (Object*) (o)->Clone();
	case TYPE_STRING:
		return (Object*)(o)->Clone();
	case TYPE_BOOL:
		return (Object*) (o)->Clone();
	case TYPE_NULL:
		return (Object*) (o)->Clone();
	case TYPE_TABLE:
		return (Object*) (o)->Clone();
	case TYPE_FUNCTION:
		return (Object*) (o)->Clone();
	case TYPE_OBJECT:
		return o->Clone();
	default:
		return nullptr;
	}
}

Object* Fuse::Clone(std::shared_ptr<Object> o) {
	return Clone(o.get());
}

Type Fuse::Object::GetType() {
	return type;
}

Object* Fuse::Object::Clone() {
	
}

std::string Fuse::Object::ToString() {
	return "";
}

// null
Null* Null::Clone() {
	auto n = new Null();
	*n = *this;
	return n;
}

std::string Null::ToString() {
	return "null";
}