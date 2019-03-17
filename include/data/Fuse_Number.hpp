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
		INumber() { ; }
		INumber(long long _long): type(INUM_TYPE::INT), INT(_long) { ; }
		INumber(double _double): type(INUM_TYPE::DOUBLE), DOUBLE(_double) { ; }
		
		char type = INT;
		union {
			long long INT = 0x0;
			double DOUBLE;
		};
	};
	
	class Number : public Object {
	public:
		Number();
		Number(long long _long): val(_long) { ; }
		Number(double _double): val(_double) { ; }
		Number(INumber _inum): val(_inum) { ; }
		Number* Clone();
		
		Type GetType();
		
		INumber& GetNum();
		std::string ToString();
	private:
		INumber val;
	};
	
};