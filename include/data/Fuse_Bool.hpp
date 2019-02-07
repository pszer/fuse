#pragma once

#include "data/Fuse_Object.hpp"

namespace Fuse {
	
	class Bool : Object {
	public:
		Bool();
		Bool(bool _val): val(_val) { ; }
		
		Bool* Clone();
		bool& Value();
		
		std::string ToString();
	private:
		Type type = TYPE_BOOL;
		bool val = false;
	};
	
};