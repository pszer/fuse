#include "Fuse_Core.hpp"

namespace __gnu_cxx
{
    void __verbose_terminate_handler()
    {
        for (;;)
            ;
    }
}

using namespace Fuse;

struct Fuse::Core Fuse::Core;

static std::shared_ptr<Object> _null = std::make_shared<Null>();
std::shared_ptr<Object> Fuse::NullReturn() {
	return _null;
}

Core::Core(): _Parser( Parser(&_Lexer) ) {
	InitOperations();
	IO_Library();
}

int Core::SetReader(std::istream* _stream) {
	return _Lexer.SetReader(_stream);
}

void Core::SetOut(std::ostream* _ostream, std::string str) {
	return _Lexer.SetOut(_ostream, str);
}

std::unique_ptr<ExprAST> Core::Parse() {
	return std::move(_Parser.ParseStatement());
}

bool Core::Error() {
	return ErrorFlag;
}

std::string Core::GetErrorMessage() {
	return ErrorMsg;
}

std::shared_ptr<Object> Core::SetErrorMessage(const std::string& str) {
	ErrorFlag = true;
	ErrorMsg = str;
	return nullptr;
}

int Core::Load(void (*handle)(std::shared_ptr<Object>)) {
	if (!_Lexer.IsStreamSet()) {
		return -1;
	}
	
	while (true) {
		if (_Lexer.IsStreamEOF()) {
			break;
		}
		
		auto stat = _Parser.ParseStatement();
		if (stat == nullptr) {
			return -1;
		}
		
		auto eval = stat->Eval();
		if (handle != nullptr)
			handle(eval);
		if (Error())
			return -1;
	}
	
	return 0;
};

void Core::AddCFunc(const std::string& name, std::shared_ptr<Object> (*Func)(std::vector<std::shared_ptr<Object>>& args), std::vector<Type> ArgTypes) {
	CreateVariable(name, CreateCFunc(Func, ArgTypes));
}

std::shared_ptr<Object> Core::CreateCFunc(std::shared_ptr<Object> (*Func)(std::vector<std::shared_ptr<Object>>& args), std::vector<Type> ArgTypes) {
	return std::make_shared<Function>(std::make_shared<FunctionAST>(Func, ArgTypes));
}

std::shared_ptr<Object> Fuse::_print(std::vector<std::shared_ptr<Object>>& args) {
	*Core._Lexer.ostream << args.at(0)->ToString() << std::endl;
	return NullReturn();
}

void Core::IO_Library() {
	auto io = CreateVariable("io", std::make_shared<Table>());
	auto io_table = dynamic_cast<Table*>(io.get());
	
	auto ConsolePrint = CreateCFunc(Fuse::_print, {TYPE_OBJECT});
	io_table->AddKey(ConsolePrint, "ConsolePrint");
}

Scope& Core::TopScope() {
	if (LocalScope == nullptr)
		return GlobalScope;
	else 
		return LocalScope->back();
}

std::shared_ptr<std::vector<Scope>> Core::EnterScope() {
	auto old_scope = LocalScope;
	LocalScope = std::make_shared<std::vector<Scope>>();
	LocalScope->emplace_back();
	return old_scope;
}

std::shared_ptr<std::vector<Scope>> Core::EnterScope(std::shared_ptr<std::vector<Scope>> new_scope) {
	auto old_scope = LocalScope;
	LocalScope = new_scope;
	if (LocalScope != nullptr && LocalScope->empty()) LocalScope->emplace_back();
	return old_scope;
}

std::shared_ptr<Fuse::Object> Core::GetVariable(const std::string& var_name) {
	if (LocalScope) {
		for (size_t i = LocalScope->size() - 1;; --i) {
			auto scope = LocalScope->at(i);
			auto v = scope.find(var_name);
			if (v != scope.end()) {
				return v->second;
			}
			
			if (i == 0) break;
		}
	}
	
	auto v = GlobalScope.find(var_name);
	if (v != GlobalScope.end()) {
		return v->second;
	}
	
	return nullptr;
}

std::shared_ptr<Fuse::Object> Core::CallFunction(const std::string& func_name, std::vector< std::shared_ptr<Object> >& call_args) {
	auto func = GetVariable(func_name);
	if (func == nullptr) return nullptr;
	return dynamic_cast<Function*>(func.get())->Call(call_args);
}

VAR_SET_STATE Core::SetVariable(const std::string& var_name, std::shared_ptr<Fuse::Object> obj) {
	auto var = GetVariable(var_name);
	
	if (var == nullptr) return ERROR;
	else var = obj;
	return SUCCESS;
}

std::shared_ptr<Fuse::Object> Core::CreateVariable(const std::string& var_name, std::shared_ptr<Fuse::Object> obj) {
	if (LocalScope) {
		LocalScope->back()[var_name] = obj;
		return LocalScope->back()[var_name];
	} else {
		GlobalScope[var_name] = obj;
		return GlobalScope[var_name];
	}
}

bool Core::IsVariableLocal(const std::string& str) {
	auto v = GlobalScope.find(str);
	if (v != GlobalScope.end()) return false;
	return true;
}