#include "Fuse_Core.hpp"

int main(int argc, char** argv) {
	std::stringstream str("print(\"Hello World!\");");
	
	Fuse::Core core;
	core.Lexer.SetReader(str);
	
	while (1) {
		int token = core.Lexer.GetNextToken();
		
		std::cout << core.Lexer.TokenToString(token) << " ";
		if (token == Fuse::TOK_EOF) break;
	}
	std::cout << std::endl;
	
	return 0;
}