#include "Parser.hpp"

using namespace Fuse;

std::unique_ptr<StatAST> Parser::StatLogError(const std::string& str) {
	std::cerr << "\033[0;31mERROR\033[0m: " << str << std::endl;
	return nullptr;
}

std::unique_ptr<ExprAST> Parser::ExprLogError(const std::string& str) {
	std::cerr << "\033[0;31mERROR\033[0m: " << str << std::endl;
	return nullptr;
}

void Parser::LogWarning(const std::string& str) {
	std::cerr << "\033[1;33mWarning\033[0m:: " << str << std::endl;
}

Parser_State Parser::Parse() {
	return PARSER_SUCCESS;
}

int Parser::GetNextToken() { return CurrTok = lex->GetNextToken(); }
int Parser::GetCurrentToken() { return CurrTok; }

std::unique_ptr<StatAST> Parser::ParseStatement() {
	return nullptr;	
}
		
std::unique_ptr<StatAST> Parser::ParseFuncDef() {
	return nullptr;	
}

std::unique_ptr<ExprAST> Parser::ParseLambdaDef() {
	return nullptr;	
}
		
std::unique_ptr<StatAST> Parser::ParseBlock() {
	return nullptr;	
}

std::unique_ptr<StatAST> Parser::ParseReturn() {
	return nullptr;	
}
		
		
std::unique_ptr<ExprAST> Parser::ParseExpression() {
	return nullptr;	
}
		
std::unique_ptr<ExprAST> Parser::ParseNumber() {
	return nullptr;	
}

std::unique_ptr<ExprAST> Parser::ParseString() {
	return nullptr;
}

std::unique_ptr<ExprAST> Parser::ParseBoolean() {
	if (GetCurrentToken() == TOK_FALSE) {
		return nullptr;
	} else {
		return nullptr;
	}
}