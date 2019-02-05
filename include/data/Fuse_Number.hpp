#pragma once

#include "data/Fuse_Object.hpp"

namespace Fuse {
	
	/*
	A Fuse::Number is a general data type for both integers
	and doubles, the current type of it is stored in
	this->val.type which will equal the enumerations INT or DOUBLE.
	By default it is an INT equal to 0ll.
	*/
	
	// Intermediate number struct
	enum INUM_TYPE { INT , DOUBLE };
	struct INumber {
		char type = INT;
		union {
			long long INT = 0x0;
			double DOUBLE;
		};
	};
	
	class Number : Object {
	public:
		Number();
		Number* Clone();
		
		INumber& GetNum();
		std::string ToString();
	private:
		Type type = TYPE_NUMBER;
		INumber val;
	};
	
};