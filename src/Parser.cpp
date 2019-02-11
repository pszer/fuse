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
	switch (GetCurrentToken()) {
	case TOK_FUNCTION:
		return ParseFuncDef();
	case '{':
		return ParseBlock();
	default:
		return StatLogError("Invalid statement");
	}
}
		
std::unique_ptr<StatAST> Parser::ParseFuncDef() {
	GetNextToken(); // eat 'function' keyword
	
	std::string Name;
	if (GetCurrentToken() != TOK_IDENTIFIER) {
		return StatLogError("Expected identifier in function definition statement for the function's name");
	}
	Name = lex->IdName;
	
	if (GetNextToken() != '(') {
		return StatLogError("Expected '(' for functions arguments");
	}
	
	std::vector<std::string> Args;
	bool expect_comma = false;
	while (1) {
		GetNextToken();
		
		if (GetCurrentToken() == ')') break;
		
		if (GetCurrentToken() == TOK_IDENTIFIER) {
			if (expect_comma) return StatLogError("Expected ',' before next function argument");
			Args.push_back(lex->IdName);
			expect_comma = true;
		} else if (expect_comma && (GetCurrentToken() == ',')) {
			expect_comma = false;
		} else {
			return StatLogError("Unexpected token in function arguments");
		}
	}
	
	auto Body = Parser::ParseStatement();
	auto Func = std::make_shared<FunctionAST> (Args, std::move(Body));
	
	_Core->CreateVariable(Name, std::make_shared<Function>(Func));
	
	return std::move( std::make_unique<FuncDefStatAST>(Func) );
}

std::unique_ptr<ExprAST> Parser::ParseLambdaDef() {
	GetNextToken(); // eat 'function' keyword
	
	if (GetCurrentToken() == TOK_IDENTIFIER) {
		return ExprLogError("Unexpected function name for anonymous function expression");
	}
	
	if (GetCurrentToken() != '(') {
		return ExprLogError("Expected '(' for functions arguments");
	}
	
	std::vector<std::string> Args;
	bool expect_comma = false;
	while (1) {
		GetNextToken();
		
		if (GetCurrentToken() == ')') break;
		
		if (GetCurrentToken() == TOK_IDENTIFIER) {
			if (expect_comma) return ExprLogError("Expected ',' before next function argument");
			Args.push_back(lex->IdName);
			expect_comma = true;
		} else if (expect_comma && (GetCurrentToken() == ',')) {
			expect_comma = false;
		} else {
			return ExprLogError("Unexpected token in function arguments");
		}
	}
	
	auto Body = Parser::ParseStatement();
	auto Func = std::make_shared<FunctionAST> (Args, std::move(Body));
	
	return std::move( std::make_unique<FuncDefExprAST>(Func) );
}
		
std::unique_ptr<StatAST> Parser::ParseBlock() {
	GetNextToken(); // eat '{' character
	
	std::vector<std::unique_ptr<StatAST>> Stats;
	while (GetCurrentToken() != '}') {
		if (GetCurrentToken() == TOK_EOF)
			return StatLogError("Reached EOF while expected '}'");
			
		Stats.push_back( Parser::ParseStatement() );
	}
	
	GetNextToken(); // eat '}'
	
	return std::move( std::make_unique<BlockAST>(Stats) );
}

std::unique_ptr<StatAST> Parser::ParseReturn() {
	GetNextToken(); // eat 'return' keyword
	return std::move( std::make_unique<ReturnAST>( Parser::ParseExpression() ) );
}
		
std::unique_ptr<ExprAST> ParseExprPrimary() {
	
}
		
std::unique_ptr<ExprAST> Parser::ParseExpression() {
	auto LHS = ParseExprPrimary();
}
		
std::unique_ptr<ExprAST> Parser::ParseNumber() {
	auto result = std::make_unique<NumberAST>( (lex->IsInt ? lex->IntVal : lex->DoubleVal) );
	GetNextToken();
	return std::move(result);
}

std::unique_ptr<ExprAST> Parser::ParseString() {
	auto result = std::make_unique<StringAST>( lex->String );
	GetNextToken();
	return std::move(result);
}

std::unique_ptr<ExprAST> Parser::ParseBoolean() {
	if (GetCurrentToken() == TOK_FALSE) {
		return std::move( std::make_unique<BoolAST>(false) );
	} else {
		return std::move( std::make_unique<BoolAST>(true) );
	}
}