#include "ast/TableAccess.hpp"
#include "Fuse_Core.hpp"

using namespace Fuse;

std::shared_ptr<Fuse::Object> TableAccessAST::Eval() {
	auto t = table->Eval();
	if (t == nullptr) return nullptr;
	if (dynamic_cast<Table*>(t.get()) == nullptr) {
		return Core.SetErrorMessage("trying to index a non-table object");
	}
	
	auto index = access->Eval();
	if (index == nullptr)
		return nullptr;
	if (dynamic_cast<Number*>(index.get()) != nullptr) {
		auto num = dynamic_cast<Number*>(index.get())->GetNum();
		std::size_t index;
		if (num.type == DOUBLE)
			index = (std::size_t)num.DOUBLE;
		else
			index = num.INT;
			
		auto element = dynamic_cast<Table*>(t.get())->Access(index);
		if (element == nullptr) return nullptr;
		return element;
	} else {
		std::string key = index->ToString();
		auto element = dynamic_cast<Table*>(t.get())->Access(key);
		if (element == nullptr) return nullptr;
		return element;
	}
}

TypeAST TableAccessAST::GetType() {
	return NODE_TABLE_ACCESS;
}

std::shared_ptr<Object> TableAccessAST::Assign(std::shared_ptr<Object> obj) {
	auto t = table->Eval();
	if (t == nullptr) return nullptr;
	if (dynamic_cast<Table*>(t.get()) == nullptr) {
		Core.SetErrorMessage("trying to index a non-table object");
		return nullptr;
	}
	
	auto index = access->Eval();
	if (dynamic_cast<Number*>(index.get()) != nullptr) {
		auto num = dynamic_cast<Number*>(index.get())->GetNum();
		std::size_t index;
		if (num.type == DOUBLE)
			index = (std::size_t)num.DOUBLE;
		else
			index = num.INT;
			
		return dynamic_cast<Table*>(t.get())->Assign(index, obj);
	} else {
		std::string key = index->ToString();
		return dynamic_cast<Table*>(t.get())->Assign(key, obj);
	}
}