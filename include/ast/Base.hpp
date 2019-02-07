#pragma once

#include <vector>

// For data/Fuse_Function.hpp
namespace Fuse { class FunctionAST; };

#include "data/Fuse_Object.hpp"

/*

chunk ::= { statement ‘;’ } [laststat ‘;’]

block ::= ‘{‘ chunk ‘}’ | statement

statement ::= var ‘=’ exp |
		functioncall |
		block |
		while ‘(‘ exp ‘)’ block |
		do block while ‘(‘ exp ‘)’ |
		if ‘(‘ exp ‘) block { else block } |
		for ‘(‘ var ‘=’ exp ‘;’ [exp] ‘;’ exp ‘)’ block |
		for ‘(‘ [new] var in exp ‘)’ block |
		switch ‘(‘ exp ‘)’ ‘{‘ { case ‘(‘ explist ‘)’ block } ‘}’ |
		function funcname funcbody

laststat ::= return [exp] | break

exp ::= NULL | false | true | Number | String | function | prefixexp |
        tableconstructor | exp binop exp | prefixunop exp | exp postunop

var ::= Name | prefixexp ‘[‘ exp ‘]’ | prefixexp ‘.’ Name

function ::= function funcbody

funcname ::= Name { ‘.’ Name } 

funcbody ::= ‘(‘ [namelist] ‘)’ block

functioncall ::= prefixexp args

prefixexp ::= var | functioncall | ‘(‘ exp ‘)’

namelist ::= { Name ‘,’ } Name

explist ::= { exp ‘,’ } exp

args ::= ‘(‘ [explist] ‘)’

tableconstructor ::= ‘{‘ [entrylist] ‘}’

entrylist ::= entry { ‘,’ entry } [‘,’]

entry ::= ‘[‘ exp ‘]’ ‘=’ exp | Name ‘=’ exp | exp

binop ::= ‘+’ | ‘-’ | ‘*’ | ‘/’ | ‘%’ | ‘^’ |
          ‘==’ | ‘!=’ | ‘>’ | ‘<’ | ‘<=’ | ‘>=’ |
          and | or |

prefixunop ::= ‘-’ | ‘++’ | ‘--’ | not

postunop ::= ‘++’ | ‘--’

*/

namespace Fuse {
	
	enum TypeAST : char {
		NODE_BLOCK, NODE_RETURN, NODE_NULL,
		
		NODE_OBJECT, NODE_VARIABLE,
		
		// number, string and boolean literals
		NODE_NUMBER, NODE_STRING, NODE_BOOL,
		
		NODE_ASSIGN, NODE_BIN_EXPR, NODE_UNOP_EXPR, NODE_FUNC_CALL,
		
		NODE_IF_ELSE, NODE_WHILE, NODE_DO,
		NODE_FOR, NODE_SWITCH,
		
		NODE_FUNC_DEF,  NODE_TABLE_DEF
	};
	
	
	/*
	
	StatAST is the base class for all statement nodes.
	
	statement ::= var ‘=’ exp |
	              functioncall |
	              block |
	              while ‘(‘ exp ‘)’ block |
	              do block while ‘(‘ exp ‘)’ |
	              if ‘(‘ exp ‘) block { else block } |
	              for ‘(‘ var ‘=’ exp ‘;’ [exp] ‘;’ exp ‘)’ block |
	              for ‘(‘ [new] var in exp ‘)’ block |
	              switch ‘(‘ exp ‘)’ ‘{‘ { case ‘(‘ explist ‘)’ block } ‘}’ |
	              function funcname funcbody
	*/
	class StatAST {
	public:
		// Eval executes the statement.
		//
		// Eval doesn't return anything for most statements (returns nullptr)
		// Some statements like function calls do return things, in which case they
		// return a shared ptr of the object
		virtual std::shared_ptr<Fuse::Object> Eval() = 0;
		
		TypeAST GetType();
	private:
		TypeAST type = NODE_NULL;
	};
	
	
	
	/*
	
	ExprAST is the base class for all expression nodes.
	
	exp ::= NULL | false | true | Number | String | function | prefixexp |
        	tableconstructor | exp binop exp | prefixunop exp | exp postunop
	*/
	class ExprAST {
	public:
		// Eval evaluates the expression, all expressions evaluate to something
		// so this function should never return nullptr.
		virtual std::shared_ptr<Fuse::Object> Eval() = 0;

		TypeAST GetType();
	private:
		TypeAST type = NODE_NULL;
	};
	
	/*
	PrototypeAST is the class that holds function prototype information, as in
	the functions name (or no name if it is anonymous) and arguments/parameters with their names.
	*/
	class PrototypeAST {
	public:
		PrototypeAST(const std::string& _name, const std::vector<std::string>& _args):
			Name(_name), Args(_args) { ; }
	
		const std::string& GetName();
		const std::vector<std::string>& GetArgs();
	private:
		std::string Name;
		std::vector<std::string> Args;
	};
	
	/*
	FunctionAST is the class that represents a function object. It has a PrototypeAST that holds
	information about the function and the StatAST of the function body.
	
	FunctionAST's can be found stored in the global functions in Fuse_Core or encapsulated
	in a Fuse::Function data object.
	*/
	class FunctionAST {
	public:
		FunctionAST(PrototypeAST& _proto, std::unique_ptr<StatAST> _body):
			Proto(std::move(_proto)), Body(std::move(_body)) { ; }
		
		const std::string& GetName();
		const std::vector<std::string>& GetArgs();
	private:
		PrototypeAST Proto;
		std::unique_ptr<StatAST> Body;
	};
	
}