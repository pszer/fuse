#pragma once

#include "Lexer.hpp"
#include "data/Fuse_Object.hpp"
#include "AST.hpp"
#include "Parser.hpp"
#include "Operations.hpp"

#include <iostream>
#include <vector>
#include <memory>
#include <map>

#include "std/io.hpp"
#include "std/math.hpp"

using Scope = std::map<std::string, std::shared_ptr<Fuse::Object> >;

namespace Fuse {
	
	enum VAR_SET_STATE { SUCCESS , ERROR };
	
	std::shared_ptr<Object> NullReturn();
	
	extern struct Core {
	public:
		Core();
		
		int SetReader(std::istream* _stream);
		void SetOut(std::ostream* _ostream, std::string str = "> ");
		void SetConsoleInput(std::istream* _stream);
		
		// Returns shared_ptr pointer to variable 'var_name's object, if variable doesn't exist it returns nullptr
		std::shared_ptr<Fuse::Object> GetVariable(const std::string& var_name);
		std::shared_ptr<Fuse::Object>  CallFunction(const std::string& func_name, std::vector< std::shared_ptr<Object> >& call_args);
		// Sets variable 'var_name' to an object, if variable doesn't exist returns enum ERROR otherwise SUCCESS
		VAR_SET_STATE SetVariable(const std::string& var_name, std::shared_ptr<Fuse::Object> obj);
		std::shared_ptr<Fuse::Object> CreateVariable(const std::string& var_name, std::shared_ptr<Fuse::Object> obj);
		bool IsVariableLocal(const std::string& str);
		
		std::unique_ptr<ExprAST> Parse();
		int Load(void (*handle)(std::shared_ptr<Object>) = nullptr);
		
		void AddCFunc(const std::string& name, std::shared_ptr<Object> (*Func)(std::vector<std::shared_ptr<Object>>& args), std::vector<Type> ArgTypes);

		void IO_Library();
		void Math_Library();
		
		bool Error();
		std::string GetErrorMessage();
		std::shared_ptr<Object> SetErrorMessage(const std::string& str); // returns nullptr
		
		// Enter a new scope, returns old scope
		std::shared_ptr<std::vector<Scope>> EnterScope();
		std::shared_ptr<std::vector<Scope>> EnterScope(std::shared_ptr<std::vector<Scope>> new_scope);
		
		std::vector<Operation> Operations[OP_COUNT];
		std::vector<UnaryOperation> PreUnopOperations[PREUNARY_OP_COUNT];
		std::vector<UnaryOperation> PostUnopOperations[POSTUNARY_OP_COUNT];
		
		friend std::shared_ptr<Object> _ioConsolePrint(std::vector<std::shared_ptr<Object>>& args);
		friend std::shared_ptr<Object> _ioConsoleGetChar(std::vector<std::shared_ptr<Object>>& args);
		friend std::shared_ptr<Object> _ioConsoleGetLine(std::vector<std::shared_ptr<Object>>& args);
	private:
		Parser _Parser;
		Lexer _Lexer;
		// Returns top scope
		Scope& TopScope();
		Scope GlobalScope;
		std::shared_ptr<std::vector<Scope>> LocalScope;
		
		std::istream* iconsole = nullptr;
		
		bool ErrorFlag = false;
		std::string ErrorMsg = "";
	} Core;
};