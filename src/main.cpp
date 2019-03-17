#include "Fuse_Core.hpp"
#include "Lexer.hpp"
#include "Operations.hpp"

int main(int argc, char** argv) {
	//std::stringstream str("function foo(x,y) return x + y * x - (x * y - y)");
	std::stringstream str("foo = 100 + 305");
	
	Fuse::Core._Lexer.SetReader(str);
	
	/*while (1) {
		int token = core._Lexer.GetNextToken();
		
		std::cout << core._Lexer.TokenToString(token) << " ";
		if (token == Fuse::TOK_EOF) break;
	}*/
	
	auto result = Fuse::Core.Parse();
	std::vector< std::shared_ptr<Fuse::Object> > args;
	args.push_back( std::make_shared<Fuse::Number>(10ll) );
	args.push_back( std::make_shared<Fuse::Number>(20ll) );
	
	if (result == nullptr) {
		std::cout << "Ye itts fucked" << std::endl;
		return -1;
	}
	
	std::cout << result->GetType() << std::endl;
	std::cout << "Evalling///" << std::endl;
	result->Eval();
	std::cout << "ALL BUTTERS" << std::endl;
	
	auto foo = Fuse::Core.GetVariable("foo");
	if (foo == nullptr) {
		std::cout << "OH CRUD!!!!!!!!!" << std::endl;
	}
	std::cout << (*foo)->ToString() << std::endl;

	/*
	std::cout << "Calling :-)" << std::endl;
	auto function = (Fuse::Function*)(result->Eval().get());
	std::cout << "Actualling calling now" << std::endl;
	auto run = function->Call(args);
	auto run = Fuse::Core.CallFunction("foo", args);
	std::cout << run->ToString() << std::endl;
	*/
	
	return 0;
}