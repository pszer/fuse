#pragma once

#include "data/Fuse_Object.hpp"

namespace Fuse {
	
	class String : Object {
	public:
		String();
		String(const std::string& _str): str(_str) { ; }
		
		String* Clone();
		
		std::size_t Count(); // returns string length
		std::string& Str(); // returns reference to str
		
		std::string ToString();
	private:
		Type type = TYPE_STRING;
		std::string str = "";
	};
	
};