#pragma once

#include "Fuse_Core.hpp"

namespace Fuse {

	std::shared_ptr<Object> MakeNumber(const long long& _int);
	std::shared_ptr<Object> MakeNumber(const double& _double);
	std::shared_ptr<Object> MakeBool(const bool& _bool);
	std::shared_ptr<Object> MakeString(const std::string& str);
	std::shared_ptr<Object> MakeTable();
	std::shared_ptr<Object> MakeCFunc(std::shared_ptr<Object> (*Func)(std::vector<std::shared_ptr<Object>>& args), std::vector<Type> ArgTypes);

	Number* GetNumber(std::shared_ptr<Object> obj);
	Bool* GetBool(std::shared_ptr<Object> obj);
	String* GetString(std::shared_ptr<Object> obj);
	Table* GetTable(std::shared_ptr<Object> obj);
	Function* GetFunction(std::shared_ptr<Object> obj);
};