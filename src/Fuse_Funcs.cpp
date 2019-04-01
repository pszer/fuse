#include "Fuse_Funcs.hpp"

using namespace Fuse;

std::shared_ptr<Object> Fuse::MakeNumber(const long long& _int) {
	return std::make_shared<Number>(_int); }
std::shared_ptr<Object> Fuse::MakeNumber(const double& _double) {
	return std::make_shared<Number>(_double); }
std::shared_ptr<Object> Fuse::MakeBool(const bool& _bool) {
	return std::make_shared<Bool>(_bool); }
std::shared_ptr<Object> Fuse::MakeString(const std::string& str) {
	return std::make_shared<String>(str); }
std::shared_ptr<Object> Fuse::MakeTable() {
	return std::make_shared<Table>(); }

std::shared_ptr<Object> Fuse::MakeCFunc(std::shared_ptr<Object> (*Func)(std::vector<std::shared_ptr<Object>>& args), std::vector<Type> ArgTypes) {
	return std::make_shared<Function>(std::make_shared<FunctionAST>(Func, ArgTypes));
}

Bool* Fuse::GetBool(std::shared_ptr<Object> obj) {
	return dynamic_cast<Bool*>(obj.get()); }
Number* Fuse::GetNumber(std::shared_ptr<Object> obj) {
	return dynamic_cast<Number*>(obj.get()); }
String* Fuse::GetString(std::shared_ptr<Object> obj) {
	return dynamic_cast<String*>(obj.get()); }
Table* Fuse::GetTable(std::shared_ptr<Object> obj) {
	return dynamic_cast<Table*>(obj.get()); }
Function* Fuse::GetFunction(std::shared_ptr<Object> obj) {
	return dynamic_cast<Function*>(obj.get()); }