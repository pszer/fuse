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
		NODE_BREAK, NODE_CONTINUE,
		
		NODE_FUNC_DEF,  NODE_TABLE_DEF , NODE_TABLE_ACCESS
	};
	
	
	/*
	
	ExprAST is the base class for all expression and statement nodes.
	
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
	
	exp ::= NULL | false | true | Number | String | function | prefixexp |
        	tableconstructor | exp binop exp | prefixunop exp | exp postunop

	*/
	class ExprAST {
	public:
		// Eval evaluates the expression, all expressions evaluate to something
		// so this function should never return nullptr.
		virtual std::shared_ptr<Fuse::Object> Eval() = 0;

		virtual TypeAST GetType() = 0;
	};
	
	std::shared_ptr<Fuse::Object> ScopedEval(std::unique_ptr<ExprAST>& ast);
	
	class FunctionAST {
	public:
		FunctionAST(const std::vector<std::string>& _args, std::unique_ptr<ExprAST> _body):
		  Args(_args), Body(std::move(_body)) { ; }
		FunctionAST(std::shared_ptr<Object> (*_CFunc)(std::vector<std::shared_ptr<Object>>& args),
		  std::vector<Type>& _CFuncArgTypes): CFunc(_CFunc), CFuncArgTypes(_CFuncArgTypes) { ; }

		const std::vector<std::string>& GetArgs();
		const ExprAST * GetBody();
		
		std::shared_ptr<Fuse::Object> Call(std::vector< std::shared_ptr<Object> >& call_args);
		bool IsCFunc();
	private:
		std::vector<std::string> Args;
		std::unique_ptr<ExprAST> Body;
		
		std::vector<Type> CFuncArgTypes;
		std::shared_ptr<Object> (*CFunc)(std::vector<std::shared_ptr<Object>>& args) = nullptr;
		
		std::shared_ptr<Fuse::Object> CallFuseFunc(std::vector< std::shared_ptr<Object> >& call_args);
		std::shared_ptr<Fuse::Object> CallCFunc(std::vector< std::shared_ptr<Object> >& call_args);
	};
	
	class VoidAST : public ExprAST {
	public:
		VoidAST() { ; }
		std::shared_ptr<Fuse::Object> Eval();
		TypeAST GetType();
	};
}