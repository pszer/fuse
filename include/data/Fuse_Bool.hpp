#pragma once

#include "data/Fuse_Object.hpp"

namespace Fuse {
	
	class Bool : public Object {
	public:
		Bool();
		Bool(bool _val): val(_val) { ; }
		
		Type GetType();
		
		Bool* Clone();
		bool& Value();
		
		std::string ToString();
		bool IsTrue();
	private:
		Type type = TYPE_BOOL;
		bool val = false;
	};
	
};