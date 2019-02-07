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
	Fuse::Number* num = new Fuse::Number(num->GetNum());
	num->GetNum() = INum;
	return std::shared_ptr<Object>((Object*)num);
}

std::shared_ptr<Fuse::Object> StringAST::Eval() {
	Fuse::String* str = new Fuse::String(str->Str());
	return std::shared_ptr<Object>((Object*)str);
}

std::shared_ptr<Fuse::Object> BoolAST::Eval() {
	Fuse::Bool* b = new Fuse::Bool(b->Value());
	return std::shared_ptr<Object>((Object*)b);
}