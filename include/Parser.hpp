#pragma once

#include "AST.hpp"
#include "Lexer.hpp"
#include "data/Fuse_Object.hpp"

namespace Fuse { class Core; }

namespace Fuse {
	
	enum Parser_State { PARSER_SUCCESS , PARSER_WARNING , PARSER_ERROR , PARSER_EOF };
	
	struct Parser {
		Parser(Fuse::Lexer* _l, Core * _core, VariableScopes* _scopes): lex(_l), _Core(_core), _Scopes(_scopes) { ; }
		
		std::unique_ptr<StatAST> Parse();
	private:
		using VariableScopes = std::vector< std::map<std::string, std::shared_ptr<Fuse::Object>> >;
		VariableScopes * _Scopes;
		Fuse::Core * _Core;
	
		int GetNextToken();
		int GetCurrentToken();
		int CurrTok;
	
		std::unique_ptr<StatAST> StatLogError(const std::string& );
		std::unique_ptr<ExprAST> ExprLogError(const std::string& );
		void LogWarning(const std::string&);
	
		std::unique_ptr<StatAST> ParseStatement();
		
		std::unique_ptr<StatAST> ParseFuncDef();
		std::unique_ptr<ExprAST> ParseLambdaDef();
		
		std::unique_ptr<StatAST> ParseBlock();
		std::unique_ptr<StatAST> ParseReturn();
		
		std::unique_ptr<ExprAST> ParseExpression();
		std::unique_ptr<ExprAST> ParseExprPrimary();
		std::unique_ptr<ExprAST> ParseBinopRHS(int ExprPrec, std::unique_ptr<ExprAST> LHS);
		
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
		{    1 , 40 , 40 , 60 , 60 , 60 ,
		     30 , 30 , 30 , 30 , 30 ,
		     20 , 20 , 10 , 10 , 10 , 10 };
	};

};