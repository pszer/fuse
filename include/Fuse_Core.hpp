#pragma once

#include "Lexer.hpp"
#include "data/Fuse_Object.hpp"
#include "AST.hpp"
#include "Parser.hpp"
#include "Operations.hpp"

#include <vector>
#include <memory>
#include <map>

using Scope = std::map<std::string, std::shared_ptr<Fuse::Object> >;

namespace Fuse {
	
	enum VAR_SET_STATE { SUCCESS , ERROR };
	
	std::shared_ptr<Object> NullReturn();
	
	extern struct Core {
	public:
		Core();
		
		int SetReader(std::istream* _stream);
		void SetOut(std::ostream* _ostream, std::string str = "> ");
		
		// Returns shared_ptr pointer to variable 'var_name's object, if variable doesn't exist it returns nullptr
		std::shared_ptr<Fuse::Object>* GetVariable(const std::string& var_name);
		std::shared_ptr<Fuse::Object>  CallFunction(const std::string& func_name, std::vector< std::shared_ptr<Object> >& call_args);
		// Sets variable 'var_name' to an object, if variable doesn't exist returns enum ERROR otherwise SUCCESS
		VAR_SET_STATE SetVariable(const std::string& var_name, std::shared_ptr<Fuse::Object> obj);
		std::shared_ptr<Fuse::Object>* CreateVariable(const std::string& var_name, std::shared_ptr<Fuse::Object> obj);
		bool IsVariableLocal(const std::string& str);
		
		std::unique_ptr<ExprAST> Parse();
		int Load(void (*handle)(std::shared_ptr<Object>) = nullptr);
		
		void AddCFunc(const std::string& name, std::shared_ptr<Object> (*Func)(std::vector<std::shared_ptr<Object>>& args), std::vector<Type> ArgTypes);
		std::shared_ptr<Object> CreateCFunc(std::shared_ptr<Object> (*Func)(std::vector<std::shared_ptr<Object>>& args), std::vector<Type> ArgTypes);
		
		void IO_Library();
		
		
		bool Error();
		std::string GetErrorMessage();
		std::shared_ptr<Object> SetErrorMessage(const std::string& str); // returns nullptr
		
		// Enter a new scope, returns old scope
		std::shared_ptr<std::vector<Scope>> EnterScope();
		std::shared_ptr<std::vector<Scope>> EnterScope(std::shared_ptr<std::vector<Scope>> new_scope);
		
		std::vector<Operation> Operations[OP_COUNT];
	private:
		Parser _Parser;
		Lexer _Lexer;
		// Returns top scope
		Scope& TopScope();
		Scope GlobalScope;
		std::shared_ptr<std::vector<Scope>> LocalScope;
		
		bool ErrorFlag = false;
		std::string ErrorMsg = "";
	} Core;
	
	std::shared_ptr<Object> _print(std::vector<std::shared_ptr<Object>>& args);
	
};