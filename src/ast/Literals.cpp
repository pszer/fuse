#include "ast/Literals.hpp"

using namespace Fuse;

/*
Constructors
*/

NumberAST::NumberAST(long long _long) {
	INum.type = INT;
	INum.INT = _long;
}

NumberAST::NumberAST(double _double) {
	INum.type = DOUBLE;
	INum.DOUBLE = _double;
}

StringAST::StringAST(const std::string& str) {
	String = str;
}

BoolAST::BoolAST(bool _bool) {
	Bool = _bool;
}

TypeAST Fuse::NumberAST::GetType() {
	return NODE_NUMBER;
}

TypeAST Fuse::StringAST::GetType() {
	return NODE_STRING;
}

TypeAST Fuse::BoolAST::GetType() {
	return NODE_BOOL;
}

/*
Get functions
*/

Fuse::INumber& NumberAST::GetNum() {
	return INum;
}

std::string& StringAST::GetString() {
	return String;
}

bool& BoolAST::GetBool() {
	return Bool;
}

/*
Eval functions
*/

std::shared_ptr<Fuse::Object> NumberAST::Eval() {
	std::cout << "num eval" << std::endl;
	return std::make_shared<Fuse::Number>(INum);
}

std::shared_ptr<Fuse::Object> StringAST::Eval() {
	return std::make_shared<Fuse::String>(String);
}

std::shared_ptr<Fuse::Object> BoolAST::Eval() {
	return std::make_shared<Fuse::Bool>(Bool);
}