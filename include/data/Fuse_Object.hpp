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
		TYPE_SIGNAL ,
		TYPE_UNINITIALIZED 
	};
	
	const std::string TypeName[] = {
		"Object",
		"Null",
		"Number",
		"String",
		"Bool",
		"Table",
		"Function",
		"Signal",
		"Uninitialized"
	};

	class Object {
	public:
		virtual Type GetType(); // returns type
		virtual std::shared_ptr<Object> Clone();   // returns nullptr
		
		virtual std::string ToString();
		virtual bool IsTrue();
	private:
	};
	
	class Null : public Object {
	public:
		std::shared_ptr<Object> Clone();
		std::string ToString();
		
		Type GetType();
		bool IsTrue();
	};
	
	enum Sig : char {
		SIG_BREAK,
		SIG_CONTINUE
	};
	
	class Signal : public Object {
	public:
		Signal(Sig _s): SIGNAL(_s) { ; }
	
		std::shared_ptr<Object> Clone();
		std::string ToString();
		
		Type GetType();
		bool IsTrue();
		Sig SIGNAL;
	};

};

#include "data/Fuse_Object.hpp"
#include "data/Fuse_Table.hpp"
#include "data/Fuse_Number.hpp"
#include "data/Fuse_String.hpp"
#include "data/Fuse_Bool.hpp"
#include "data/Fuse_Function.hpp"