#pragma once

#include "AST.hpp"
#include "Lexer.hpp"
#include "data/Fuse_Object.hpp"

namespace Fuse {
	
	struct Parser {
		Parser(Fuse::Lexer* _l): lex(_l) { ; }
	private:
		Fuse::Lexer* lex;
	};

};