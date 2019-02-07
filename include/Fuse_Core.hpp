#pragma once

#include "Lexer.hpp"
#include "Parser.hpp"

namespace Fuse {
	
	class Core {
	public:
		Core();
		
		Parser _Parser;
		Lexer _Lexer;
	private:
	};
	
};