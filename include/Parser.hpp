#pragma once

#include "AST.hpp"
#include "Lexer.hpp"
#include "data/Fuse_Object.hpp"

namespace Fuse { class Core; }

namespace Fuse {
	
	enum Parser_State { PARSER_SUCCESS , PARSER_WARNING , PARSER_ERROR , PARSER_EOF };
	
	struct Parser {
		Parser(Fuse::Lexer* _l, VariableScopes* _scopes): lex(_l) { ; }
		
		std::unique_ptr<ExprAST> Parse();
	private:
		int GetNextToken();
		int GetCurrentToken();
		int CurrTok;
	
		std::unique_ptr<ExprAST> StatLogError(const std::string& );
		std::unique_ptr<ExprAST> ExprLogError(const std::string& );
		void LogWarning(const std::string&);
	
		std::unique_ptr<ExprAST> ParseExpression();
		std::unique_ptr<ExprAST> ParsePrimary();
		
		std::unique_ptr<ExprAST> ParseFuncDef();
		std::unique_ptr<ExprAST> ParseLambdaDef();
		
		std::unique_ptr<ExprAST> ParseBlock();
		std::unique_ptr<ExprAST> ParseReturn();
		std::unique_ptr<ExprAST> ParseIdentifier();
		std::unique_ptr<ExprAST> ParseFuncCall(std::unique_ptr<ExprAST>& expr);
		std::unique_ptr<ExprAST> ParseAssign(std::unique_ptr<ExprAST>& expr);
		
		std::unique_ptr<ExprAST> ParseBinopRHS(int ExprPrec, std::unique_ptr<ExprAST> LHS);
		
		std::unique_ptr<ExprAST> ParsePrefix(std::unique_ptr<ExprAST> expr);
		std::unique_ptr<ExprAST> ParseVariable();
		
		std::unique_ptr<ExprAST> ParsePreUnopExpr();
		std::unique_ptr<ExprAST> ParsePostUnopExpr();
		
		std::unique_ptr<ExprAST> ParseNumber();
		std::unique_ptr<ExprAST> ParseString();
		std::unique_ptr<ExprAST> ParseBoolean();
			
		Fuse::Lexer* lex;
		
		bool IsPrefixOp(OPERATORS op);
		
		int GetPrecedence(OPERATORS op);
		int GetTokenPrecedence();
		int BinopPrecedence[OP_COUNT] =
		/* OP_EQUAL, OP_ADD, OP_SUB, OP_MULT, OP_DIV, OP_MODULO,
		   OP_COMP_EQUAL, OP_COMP_LESS, OP_COMP_GREATER, OP_COMP_LESS_EQUAL, OP_COMP_GREATER_EQUAL,
		   OP_AND, OP_OR, OP_INC, OP_DEC, OP_NEGATE, OP_NOT */
		{    1 , 40 , 40 , 50 , 50 , 50 ,
		     30 , 30 , 30 , 30 , 30 ,
		     20 , 20 , 10 , 10 , 10 , 10 };
	};

};