#include "data/Fuse_Object.hpp"

#include "data/Fuse_Table.hpp"
#include "data/Fuse_Number.hpp"
#include "data/Fuse_String.hpp"
#include "data/Fuse_Bool.hpp"
#include "data/Fuse_Function.hpp"

using namespace Fuse;

Object* Fuse::Clone(Object* o) {
	switch (o->GetType()) {
	case TYPE_NUMBER:
		return (Object*) ((Fuse::Number*)o)->Clone();
	case TYPE_STRING:
		return (Object*) ((Fuse::String*)o)->Clone();
	case TYPE_BOOL:
		return (Object*) ((Fuse::Bool*)o)->Clone();
	case TYPE_NULL:
		return (Object*) ((Fuse::Null*)o)->Clone();
	case TYPE_TABLE:
		return (Object*) ((Fuse::Table*)o)->Clone();
	case TYPE_FUNCTION:
		return (Object*) ((Fuse::Function*)o)->Clone();
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
	return TYPE_OBJECT;
}

Object* Fuse::Object::Clone() {
	
}

std::string Fuse::Object::ToString() {
	return "";
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