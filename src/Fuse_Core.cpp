#include "Fuse_Core.hpp"
#include "Fuse_Funcs.hpp"

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
}

int Core::SetReader(std::istream* _stream) {
	return _Lexer.SetReader(_stream);
}

void Core::SetOut(std::ostream* _ostream, std::string str) {
	_Lexer.SetOut(_ostream, str);
}

void Core::SetConsoleInput(std::istream* _stream) {
	iconsole = _stream;
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
	CreateVariable(name, MakeCFunc(Func, ArgTypes));
}

void Core::IO_Library() {
	auto io = CreateVariable("io", MakeTable());
	auto io_table = GetTable(io);
	
	io_table->AddKey(MakeCFunc(_ioConsolePrint, {TYPE_OBJECT}), "ConsolePrint");
	io_table->AddKey(MakeCFunc(_ioConsoleGetChar, { }), "ConsoleGetChar");
	io_table->AddKey(MakeCFunc(_ioConsoleGetLine, { }), "ConsoleGetLine");
}

void Core::Math_Library() {
	auto math = CreateVariable("math", MakeTable());
	auto math_table = GetTable(math);
	
	math_table->AddKey(MakeCFunc(_mathSqrt, {TYPE_NUMBER}), "Sqrt");
	math_table->AddKey(MakeCFunc(_mathCbrt, {TYPE_NUMBER}), "Cbrt");
	
	math_table->AddKey(MakeCFunc(_mathSin, {TYPE_NUMBER}), "Sin");
	math_table->AddKey(MakeCFunc(_mathCos, {TYPE_NUMBER}), "Cos");
	math_table->AddKey(MakeCFunc(_mathTan, {TYPE_NUMBER}), "Tan");
	
	math_table->AddKey(MakeCFunc(_mathAsin, {TYPE_NUMBER}), "Asin");
	math_table->AddKey(MakeCFunc(_mathAcos, {TYPE_NUMBER}), "Acos");
	math_table->AddKey(MakeCFunc(_mathAtan, {TYPE_NUMBER}), "Atan");
	math_table->AddKey(MakeCFunc(_mathAtan, {TYPE_NUMBER, TYPE_NUMBER}), "Atan2");
	
	math_table->AddKey(MakeCFunc(_mathSinh, {TYPE_NUMBER}), "Sinh");
	math_table->AddKey(MakeCFunc(_mathCosh, {TYPE_NUMBER}), "Cosh");
	math_table->AddKey(MakeCFunc(_mathTanh, {TYPE_NUMBER}), "Tanh");
	
	math_table->AddKey(MakeCFunc(_mathExp, {TYPE_NUMBER}), "Exp");
	math_table->AddKey(MakeCFunc(_mathLog, {TYPE_NUMBER}), "Log");
	math_table->AddKey(MakeCFunc(_mathLog10, {TYPE_NUMBER}), "Log10");
	
	math_table->AddKey(MakeCFunc(_mathCeiling, {TYPE_NUMBER}), "Ceiling");
	math_table->AddKey(MakeCFunc(_mathFloor, {TYPE_NUMBER}), "Floor");
}

void Core::Table_Library() {
	auto table = CreateVariable("table", MakeTable());
	auto table_table = GetTable(table);
	
	table_table->AddKey(MakeCFunc(_tableAt, {TYPE_TABLE, TYPE_NUMBER}), "At");
	table_table->AddKey(MakeCFunc(_tableInsert, {TYPE_TABLE, TYPE_NUMBER, TYPE_OBJECT}), "Insert");
	table_table->AddKey(MakeCFunc(_tableMap, {TYPE_TABLE, TYPE_STRING, TYPE_OBJECT}), "Map");
	table_table->AddKey(MakeCFunc(_tableDelete, {TYPE_TABLE, TYPE_NUMBER}), "Delete");
	table_table->AddKey(MakeCFunc(_tableErase, {TYPE_TABLE, TYPE_STRING}), "Erase");
	table_table->AddKey(MakeCFunc(_tableSize, {TYPE_TABLE}), "Size");
	table_table->AddKey(MakeCFunc(_tableEmpty, {TYPE_TABLE}), "Empty");
	table_table->AddKey(MakeCFunc(_tableClear, {TYPE_TABLE}), "Clear");
	table_table->AddKey(MakeCFunc(_tablePush, {TYPE_TABLE, TYPE_OBJECT}), "Push");
	table_table->AddKey(MakeCFunc(_tablePop, {TYPE_TABLE}), "Pop");
	table_table->AddKey(MakeCFunc(_tableFirst, {TYPE_TABLE}), "First");
	table_table->AddKey(MakeCFunc(_tableLast, {TYPE_TABLE}), "Last");
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

void Core::StepScopeUp() {
	if (LocalScope)
		LocalScope->emplace_back();
}
void Core::StepScoreDown() {
	if (LocalScope && !LocalScope->empty())
		LocalScope->pop_back();
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