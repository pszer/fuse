#include "ast/TableAccess.hpp"

using namespace Fuse;

std::shared_ptr<Fuse::Object> TableAccessAST::Eval() {
	auto t = table->Eval();
	if ( (t == nullptr) || (dynamic_cast<Table*>(t.get()) == nullptr) ) {
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
			
		try {
			return dynamic_cast<Table*>(t.get())->Access(index);
		} catch (...) { return nullptr; }
	} else {
		std::string key = index->ToString();
		return dynamic_cast<Table*>(t.get())->Access(key);
	}
}

TypeAST TableAccessAST::GetType() {
	return NODE_TABLE_ACCESS;
}