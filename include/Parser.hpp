#pragma once

#include "AST.hpp"
#include "Lexer.hpp"
#include "data/Fuse_Object.hpp"

namespace Fuse {
	
	enum Parser_State { PARSER_SUCCESS , PARSER_WARNING , PARSER_ERROR };
	
	struct Parser {
		Parser(Fuse::Lexer* _l): lex(_l) { ; }
		
		Parser_State Parse();
	private:
		std::unique_ptr<StatAST> StatLogError(const std::string& );
		std::unique_ptr<ExprAST> ExprLogError(const std::string& );
		void LogWarning(const std::string&);
	
		std::unique_ptr<StatAST> ParseStatement();
		
		std::unique_ptr<StatAST> ParseBlock();
		
		
		
		std::unique_ptr<ExprAST> ParseExpression();
		
		std::unique_ptr<ExprAST> ParseNumber();
		std::unique_ptr<ExprAST> ParseString();
		std::unique_ptr<ExprAST> ParseBoolean();
			
		Fuse::Lexer* lex;
	};

};