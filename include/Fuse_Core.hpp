#pragma once

#include "Lexer.hpp"
#include "Parser.hpp"

using VariableScopes = std::vector< std::map<std::string, std::shared_ptr<Fuse::Object>> >;
using Scope = std::map<std::string, std::shared_ptr<Fuse::Object> >;

namespace Fuse {
	
	enum VAR_SET_STATE { SUCCESS , ERROR };
	
	class Core {
	public:
		Core();
		
		// Returns shared_ptr pointer to variable 'var_name's object, if variable doesn't exist it returns nullptr
		std::shared_ptr<Fuse::Object>* GetVariable(const std::string& var_name);
		// Sets variable 'var_name' to an object, if variable doesn't exist returns enum ERROR otherwise SUCCESS
		VAR_SET_STATE SetVariable(const std::string& var_name, std::shared_ptr<Fuse::Object> obj);
		
		std::vector< std::unique_ptr<FunctionAST> > Functions;
		// Add a new function
		FunctionAST* EmplaceFunction(const std::vector<std::string>& _args, std::unique_ptr<StatAST> _body);
		
		Parser _Parser;
		Lexer _Lexer;
	private:
	
		// Get global scope
		Scope& GlobalScope();
		// Enter a new scope
		void EnterScope();
		// Leave current scope
		void LeaveScope();
		VariableScopes Scopes;
	};
};