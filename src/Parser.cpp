#include "Parser.hpp"
#include "Fuse_Core.hpp"

using namespace Fuse;

std::unique_ptr<ExprAST> Parser::StatLogError(const std::string& str) {
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

std::unique_ptr<ExprAST> Parser::ParseStatement() {
	GetNextToken();
	auto stat = ParseExpression();
	if (stat == nullptr) {
		return nullptr;
	}
	else return std::move(stat);
}

int Parser::GetPrecedence(OPERATORS op) {
	if (op < 0 || op > OP_COUNT) return -1;
	else return BinopPrecedence[op];
}

int Parser::GetTokenPrecedence() {
	if (GetCurrentToken() != TOK_OPERATOR) return -1;
	int TokPrec = GetPrecedence(lex->Operator);
	if (TokPrec <= 0) return -1;
	return TokPrec;
}

bool Parser::IsPrefixOp(OPERATORS op) {
	if (op == OP_INC || op == OP_DEC || op == OP_NEGATE || op == OP_NOT) return true;
}

int Parser::GetNextToken() { return CurrTok = lex->GetNextToken(); }
int Parser::GetCurrentToken() { return CurrTok; }
void Parser::PutBackToken() { ; lex->PutBackToken(); }

std::unique_ptr<ExprAST> Parser::ParseExpression() {
	//std::cout << "parsing expr" << std::endl;
	auto LHS = ParsePrimary();
	if (!LHS) return nullptr;
	
	auto Binop = ParseBinopRHS(0, std::move(LHS));
	return std::move(Binop);
}

std::unique_ptr<ExprAST> Parser::ParseStrictExpression() {
		//std::cout << "parsing expr" << std::endl;
	auto LHS = ParseStrictExprPrimary();
	if (!LHS) return nullptr;
	
	auto Binop = ParseBinopRHS(0, std::move(LHS));
	return std::move(Binop);
}

std::unique_ptr<ExprAST> Parser::ParsePrimary() {
	switch (GetCurrentToken()) {
	case TOK_STRING:
		return ParseString();
	case TOK_TRUE:
	case TOK_FALSE:
		return ParseBoolean();
	case TOK_NUMBER:
		return ParseNumber();
	case TOK_FUNCTION:
		return ParseFuncDef();
	case TOK_RETURN:
		return ParseReturn();
	case TOK_IF:
		return ParseIfElse();
	case TOK_IDENTIFIER:
		return ParseIdentifier();
	case '{':
		return ParseBlock();
	case '(':
		return ParseParenExpr();
	case ';':
		return std::make_unique<VoidAST>();
	default:
		return StatLogError("Invalid statement");
	}
}

std::unique_ptr<ExprAST> Parser::ParseStrictExprPrimary() {
	switch (GetCurrentToken()) {
	case TOK_STRING:
		return ParseString();
	case TOK_TRUE:
	case TOK_FALSE:
		return ParseBoolean();
	case TOK_NUMBER:
		return ParseNumber();
	case TOK_FUNCTION:
		return ParseLambdaDef();
	case TOK_IDENTIFIER:
		return ParseIdentifier();
	case '{':
		return ParseTableConstructor();
	case '(':
		return ParseParenExpr();
	case ';':
		return std::make_unique<VoidAST>();
	default:
		return StatLogError("Invalid statement");
	}
}

std::unique_ptr<ExprAST> Parser::ParseParenExpr() {
	GetNextToken(); // eat '('
	auto V = ParseExpression();
	if (V == nullptr) return nullptr;
	
	if (GetCurrentToken() != ')')
		return ExprLogError("Expected ')'");
	GetNextToken();
	return V;
}
		
std::unique_ptr<ExprAST> Parser::ParseFuncDef() {
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
	
	GetNextToken(); // eat ')'
	
	auto Body = Parser::ParseExpression();
	if (Body == nullptr) return nullptr;
	auto Func = std::make_shared<FunctionAST> (Args, std::move(Body));
	if (Func == nullptr) return nullptr;
	
	Core.CreateVariable(Name, std::make_shared<Function>(Func));
	
	return std::move( std::make_unique<FuncDefExprAST>(Func) );
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
	
	GetNextToken(); // eat ')'
	
	auto Body = Parser::ParseExpression();
	auto Func = std::make_shared<FunctionAST> (Args, std::move(Body));
	GetNextToken();
	
	return std::move( std::make_unique<FuncDefExprAST>(Func) );
}
		
std::unique_ptr<ExprAST> Parser::ParseBlock() {
	GetNextToken(); // eat '{' character
	
	std::vector<std::unique_ptr<ExprAST>> Stats;
	while (GetCurrentToken() != '}') {
		if (GetCurrentToken() == TOK_EOF)
			return StatLogError("Reached EOF while expected '}'");
			
		auto stat = ParseExpression();
		if (stat == nullptr) return nullptr;
		Stats.push_back( std::move(stat) );
		
		GetNextToken();
	}
	
	return std::move( std::make_unique<BlockAST>(Stats) );
}

std::unique_ptr<ExprAST> Parser::ParseReturn() {
	GetNextToken(); // eat 'return' keyword
	auto Expr = ParseExpression();
	if (Expr == nullptr)
		return nullptr;
	return std::make_unique<ReturnAST>( Expr );
}

std::unique_ptr<ExprAST> Parser::ParseIdentifier() {
	auto expr = ParsePrefix(nullptr);
	if (expr == nullptr) return nullptr;
	
	// var ‘=’ exp
	if (GetCurrentToken() == TOK_OPERATOR && lex->Operator == OP_EQUAL) {
		return ParseAssign(expr);
	} else if (GetCurrentToken() == '(') {
		return ParseFuncCall(expr);
	} else {
		return std::move(expr);
	}
}

std::unique_ptr<ExprAST> Parser::ParseFuncCall(std::unique_ptr<ExprAST>& expr) {
	GetNextToken(); // eat '('
	
	std::vector<std::unique_ptr<ExprAST>> Args;
	bool first = true;
	while (1) {
		if (GetCurrentToken() == ')') {
			GetNextToken(); // eat ')'
			break;
		}
		
		if (!first && GetCurrentToken() != ',') {
			return ExprLogError("Expected ',' in function call arguments");
		}
		
		auto arg = ParseExpression();
		Args.push_back(std::move(arg));
		first = false;
	}
	
	return std::make_unique<FuncCallAST>(std::move(expr), Args);
}

std::unique_ptr<ExprAST> Parser::ParseIfElse() {
	GetNextToken(); // eat 'if'
	
	if (GetCurrentToken() != '(') {
		return StatLogError("Expected '(' for if-statement condition");
	} else GetNextToken(); // eat '('
	
	auto cond = ParseExpression();
	if (cond == nullptr) return nullptr;
	
	if (GetCurrentToken() != ')') {
		return StatLogError("Expected ')' at the end of an if-statement condition");
	} else GetNextToken(); // eat ')'
	
	auto body = ParseExpression();
	if (body == nullptr) return nullptr;
	GetNextToken();
	
	if (GetCurrentToken() == TOK_ELSE) {
		GetNextToken(); // eat 'else'
		auto else_body = ParseExpression();
		if (else_body == nullptr) return nullptr;
		return std::make_unique<IfElseAST>(std::move(cond), std::move(body), std::move(else_body));
	} else {
		PutBackToken();
		auto ifelse = std::make_unique<IfElseAST>(std::move(cond), std::move(body));
		return std::move(ifelse);
	}
}

std::unique_ptr<ExprAST> ParseWhile() {
	return nullptr;
}

std::unique_ptr<ExprAST> Parser::ParseAssign(std::unique_ptr<ExprAST>& expr) {
	GetNextToken(); // eat '='
	auto RHS = ParseStrictExpression();
	if (RHS == nullptr) return nullptr;
	
	return std::make_unique<AssignAST>(std::move(expr), std::move(RHS));
}

std::unique_ptr<ExprAST> Parser::ParsePrefix(std::unique_ptr<ExprAST> expr) {
	// '(' exp ')'
	/*if (GetCurrentToken() == '(' && expr == nullptr) {
		GetNextToken(); // eat '('
		
		//auto pre = Parser::ParsePrefix(std::move(expr));
		auto pre = Parser::ParsePrimary();
		return std::move(pre);
	}*/
	
	std::unique_ptr<ExprAST> var, temp;
	if (!expr)
		var = ParseVariable();
	else
		var = std::move(expr);
	switch (GetCurrentToken()) {
	// funccall
	case '(':
		return ParsePrefix(ParseFuncCall(var));
	// var ::= Name | prefixexp ‘[‘ exp ‘]’ | prefixexp ‘.’ Name
	case '[':
		return ParsePrefix(ParseTableAccess(var));
	case '.':
		return ParsePrefix(ParseMemberAccess(var));
	default:
		return std::move(var);
	}
	
	return nullptr;
}


std::unique_ptr<ExprAST> Parser::ParseVariable() {
	auto var = std::make_unique<VariableAST>(lex->IdName);
	GetNextToken(); // eat var identifier
	return std::move(var);
}
		
std::unique_ptr<ExprAST> Parser::ParseBinopRHS(int ExprPrec, std::unique_ptr<ExprAST> LHS) {
	while (1) {
		int TokPrec = GetTokenPrecedence();
		
		if (TokPrec < ExprPrec) {
			return std::move(LHS);
		}
			
		OPERATORS Binop = lex->Operator;
		GetNextToken(); // eat binop
		
		auto RHS = ParsePrimary();
		if (!RHS) return nullptr;
		
		int NextPrec = GetTokenPrecedence();
		
		if (TokPrec < NextPrec) {
			RHS = ParseBinopRHS(TokPrec + 1, std::move(RHS));
			if (!RHS) return nullptr;
		}
		
		LHS = std::make_unique<BinaryExprAST>(std::move(LHS), std::move(RHS), Binop);
	}
}

std::unique_ptr<ExprAST> Parser::ParsePreUnopExpr() {
	
}

std::unique_ptr<ExprAST> Parser::ParsePostUnopExpr() {
	
}
		
std::unique_ptr<ExprAST> Parser::ParseNumber() {
	std::unique_ptr<ExprAST> result;
	if (lex->IsInt)
		result = std::make_unique<NumberAST>( lex->IntVal );
	else
		result = std::make_unique<NumberAST>( lex->DoubleVal );
	GetNextToken();
	return std::move(result);
}

std::unique_ptr<ExprAST> Parser::ParseString() {
	auto result = std::make_unique<StringAST>( lex->String );
	GetNextToken();
	return std::move(result);
}

std::unique_ptr<ExprAST> Parser::ParseBoolean() {
	std::unique_ptr<BoolAST> bool_ast;
	if (GetCurrentToken() == TOK_FALSE)
		bool_ast = std::make_unique<BoolAST>(false);
	else
		bool_ast = std::make_unique<BoolAST>(true);
	GetNextToken(); // eat 'true'/'false'
		
	return bool_ast;
}

std::unique_ptr<ExprAST> Parser::ParseTableConstructor() {
	GetNextToken(); // eat '{'
	
	std::vector<TableConstructEntry> table;
	while (true) {
		if (GetCurrentToken() == '}') {
			break;
		}
		
		auto expr = ParseStrictExpression();
		if (expr == nullptr) return nullptr;
		
		if (GetCurrentToken() == ':') {
			GetNextToken(); // eat '='
			
			auto expr2 = ParseStrictExpression();
			if (expr2 == nullptr) return nullptr;
			
			table.emplace_back(std::move(expr), std::move(expr2));
		} else {
			table.emplace_back(std::move(expr));
		}
		
		if (GetCurrentToken() != ',' && GetCurrentToken() != '}') {
			return ExprLogError("Expected ',' or '}' in table constructor");
		} else if (GetCurrentToken() == ',') {
			GetNextToken();
		}
	}
	
	auto t_expr = std::make_unique<TableConstructorAST>(table);
	GetNextToken(); // eat '}'
	return std::move(t_expr);
}

std::unique_ptr<ExprAST> Parser::ParseTableAccess(std::unique_ptr<ExprAST>& expr) {
	GetNextToken(); // eat '['
	auto access = ParseExpression();
	if (access == nullptr) return nullptr;
	
	if (GetCurrentToken() != ']') {
		return ExprLogError("']' expected for table access");
	}
	
	GetNextToken(); // eat ']'
	return std::make_unique<TableAccessAST>(std::move(expr), std::move(access));
}

std::unique_ptr<ExprAST> Parser::ParseMemberAccess(std::unique_ptr<ExprAST>& expr) {
	GetNextToken();
	if (GetCurrentToken() != TOK_IDENTIFIER) {
		return ExprLogError("Table access using '.' expects an identifier");
	}
	
	std::string id = lex->IdName;
	auto str = std::make_unique<StringAST>(id);
	GetNextToken();
	return std::make_unique<TableAccessAST>(std::move(expr), std::move(str));
}