#include "data/Fuse_Function.hpp"

using namespace Fuse;

Fuse::Function::Function() { ; }

Function* Fuse::Function::Clone() {
	return nullptr;
}

const std::string& Fuse::Function::GetName() {
	return func->GetName();
}

const std::vector<std::string>& Fuse::Function::GetArgs() {
	return func->GetArgs();
}

// Returns string representation of functions prototype
// e.g: funcname(arg1, arg2)
//      funcname()
//	
//	For an anonymous function the function name is [lambda]
//      [lambda](arg1)
std::string Fuse::Function::ToString() {
	std::string result;
	// If anonymous
	if (func->GetName() == "")
		result = "[lambda]";
	else    result = GetName();
	
	result += '(';
	
	for (auto arg = GetArgs().begin(); arg != GetArgs().end(); ++arg) {
		result += *arg;
		
		// If not last argument, put ", "
		if ((arg + 1) == GetArgs().end()) {
			result += ", ";
		}
	}
	
	result += ')';
	
	return result;
}