#pragma once

#include <iostream>
#include <istream>
#include <map>

namespace Fuse {
	
	// numbers -1 to -127 are tokens, 0-128 are
	// for unknown characters
	enum {
		TOK_EOF         = -1,
		TOK_IDENTIFIER  = -2,
		TOK_NUMBER      = -3,
		TOK_OPERATOR    = -4,
		
		TOK_IF     = -7,
		TOK_ELSE   = -8,
		TOK_WHILE  = -9,
		TOK_DO     = -10,
		
		TOK_FOR    = -11,
		TOK_IN     = -12,
		TOK_NEW    = -13,
		
		TOK_SWITCH = -14,
		TOK_CASE   = -15,
		
		TOK_FUNCTION = -16,
		TOK_RETURN   = -17,
		
		TOK_USING    = -18,
		
		TOK_TRUE     = -19,
		TOK_FALSE    = -20,
		
		TOK_BREAK    = -21,
		TOK_CONTINUE = -22,
		
		TOK_STRING = -126,
		TOK_ERROR = -127
	};
	
	enum OPERATORS {
		OP_EQUAL,
		OP_ADD, OP_SUB, OP_MULT, OP_DIV, OP_MODULO,
		
		OP_COMP_EQUAL, OP_COMP_UNEQUAL, OP_COMP_LESS, OP_COMP_GREATER, OP_COMP_LESS_EQUAL, OP_COMP_GREATER_EQUAL,
		OP_AND, OP_OR,
		
		OP_INC, OP_DEC, OP_NEGATE, OP_NOT
	};
	const int OP_COUNT = 18;
	// e.g. op_str[OP_AND] == "&&"
	const std::string op_str[] = {
		"=",
		"+", "-", "*", "/", "%",
		"==", "!=", "<", ">", "<=", ">=",
		"&&", "||",
		"++", "--", "-", "!"
	};
	
	const std::string emit_chars = ";().";
	const std::string op_chars = "=+-*/%<>&|!";
	
	enum { NO_TOK_HELD = 0xffffffff };
	struct Lexer {
		// MOVES stream into the lexer (_stream becomes invalid)
		// returns -1 if stream is empty (error), otherwise 0
		int SetReader(std::istream* _stream);
		void SetOut(std::ostream* _ostream, std::string str = "> ");
		int GetNextToken(); // returns next token
		int PutBackToken();
		bool IsStreamSet(); // returns stream_set
		bool IsStreamEOF(); // returns stream->eof()
		bool IsPosEOF();
		
		int LastToken;
		int HeldToken = NO_TOK_HELD;
		
		// if number token is an integer, IsInt is true
		// otherwise the number token is a double and
		// IsInt is false.
		bool IsInt = true;
		union {
			long long IntVal;
			double    DoubleVal;
		};
		
		// string of identifier token
		std::string IdName;
		std::string String;
		
		OPERATORS Operator;
		
		int GetLineCount();
		int GetCharCount();
		
		// Misc function for debugging
		std::string TokenToString(int tok);
	private:
		bool stream_set = false;
		std::istream* stream = nullptr; // lexer will tokenize this string stream.
		std::ostream* ostream = nullptr; // lexer will output 'text_prefix' on every newline here
		char C; // stored character used by Next()
		std::string text_prefix = "> ";
		
		int Next();
		inline void NextChar();
		void PrintTextPrefix();
		
		// Line and char for error output
		int line = 1, char_count = 0;
		
		int TokenizeKeywordId();
		int TokenizeNumber();
		int TokenizeOperator();
		int TokenizeString();
	};
};