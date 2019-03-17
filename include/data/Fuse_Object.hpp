#pragma once

#include <memory>

namespace Fuse {

	enum Type : char {
		TYPE_OBJECT, 
		TYPE_NULL ,
		TYPE_NUMBER , 
		TYPE_STRING ,
		TYPE_BOOL ,
		TYPE_TABLE ,
		TYPE_FUNCTION ,
		TYPE_UNINITIALIZED
	};

	class Object {
	public:
		virtual Type GetType(); // returns type
		virtual Object* Clone();   // returns nullptr
		
		virtual std::string ToString();
	private:
	};
	
	class Null : public Object {
	public:
		Null* Clone();
		std::string ToString();
		
		Type GetType();
	};

	Object* Clone(Object* );
	Object* Clone(std::shared_ptr<Object> );
};

#include "data/Fuse_Object.hpp"
#include "data/Fuse_Table.hpp"
#include "data/Fuse_Number.hpp"
#include "data/Fuse_String.hpp"
#include "data/Fuse_Bool.hpp"
#include "data/Fuse_Function.hpp"