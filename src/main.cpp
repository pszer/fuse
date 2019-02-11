#include "Fuse_Core.hpp"

int main(int argc, char** argv) {
	std::stringstream str("function foo(x,y) { return x + y + x; }");
	
	Fuse::Core core;
	core._Lexer.SetReader(str);
	
	while (1) {
		int token = core._Lexer.GetNextToken();
		
		std::cout << core._Lexer.TokenToString(token) << " ";
		if (token == Fuse::TOK_EOF) break;
	}
	std::cout << std::endl;
	
	return 0;
}