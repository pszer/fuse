#pragma once

#include "ast/Base.hpp"
#include "data/Fuse_Object.hpp"

namespace Fuse {

	class NumberAST : public ExprAST {
	public:
		NumberAST(long long _long);
		NumberAST(double _double);
		
		std::shared_ptr<Fuse::Object> Eval();
		Fuse::INumber& GetNum();
	private:
		Fuse::INumber INum;
		TypeAST type = NODE_NUMBER;
	};
	
	class StringAST : public ExprAST {
	public:
		StringAST(const std::string& str);
		
		std::shared_ptr<Fuse::Object> Eval();
		std::string& GetString();
	private:
		std::string String;
		TypeAST type = NODE_STRING;
	};
	
	class BoolAST : public ExprAST {
	public:
		BoolAST(bool _bool);
		
		std::shared_ptr<Fuse::Object> Eval();
		bool& GetBool();
	private:
		bool Bool;
		TypeAST type = NODE_BOOL;
	};
};