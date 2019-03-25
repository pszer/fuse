#pragma once

#include "data/Fuse_Object.hpp"

namespace Fuse {
	
	class String : public Object {
	public:
		String();
		String(const std::string& _str): str(_str) { ; }
		
		Type GetType();
		
		std::shared_ptr<Object> Clone();
		
		std::size_t Count(); // returns string length
		std::string& Str(); // returns reference to str
		
		std::string ToString();
		bool IsTrue();
	private:
		std::string str = "";
	};
	
};