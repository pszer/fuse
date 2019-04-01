#include <iostream>
#include <sstream>

#include "Fuse_Core.hpp"

void Print(std::shared_ptr<Fuse::Object>);

int main(int argc, char** argv) {
	std::cout << "Fuse test interpreter\nReady." << std::endl;
	
	Fuse::Core.IO_Library();
	Fuse::Core.Math_Library();
	Fuse::Core.Table_Library();
	
	Fuse::Core.SetOut(&std::cerr, "> ");
	Fuse::Core.SetReader(&std::cin);
	Fuse::Core.SetConsoleInput(&std::cin);
	if (Fuse::Core.Load(Print)) {
		std::cout << "FuseError : " << Fuse::Core.GetErrorMessage() << std::endl;
	}
	
	return 0;
}

void Print(std::shared_ptr<Fuse::Object> obj) {
	if (obj != nullptr && obj->GetType() != Fuse::TYPE_NULL) {
		std::string str = obj->ToString();
		if (str == "") return;
		std::cout << obj->ToString() << std::endl;
	}
}