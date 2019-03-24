#include <iostream>
#include <sstream>

#include "Fuse_Core.hpp"
#include "Lexer.hpp"
#include "Operations.hpp"

void Print(std::shared_ptr<Fuse::Object>);

int main(int argc, char** argv) {
	std::cout << "Fuse test interpreter\nReady." << std::endl;
	
	Fuse::Core._Lexer.SetOut(&std::cerr, "> ");
	Fuse::Core._Lexer.SetReader(&std::cin);
	Fuse::Core.Load(Print);
	
	return 0;
}

void Print(std::shared_ptr<Fuse::Object> obj) {
	if (obj != nullptr) {
		std::string str = obj->ToString();
		if (str == "") return;
		std::cout << obj->ToString() << std::endl;
	}
}