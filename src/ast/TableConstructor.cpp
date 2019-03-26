#include "ast/TableConstructor.hpp"

using namespace Fuse;

TypeAST Fuse::TableConstructorAST::GetType() {
	return NODE_TABLE_DEF;
}

std::shared_ptr<Fuse::Object> Fuse::TableConstructorAST::Eval() {
	auto table = std::make_shared<Table>();
	
	for (auto entry = entries.begin(); entry != entries.end(); ++entry) {
		if (entry->key == nullptr) {
			table->AddEntry(entry->expr->Eval());
		} else {
			auto obj = entry->expr->Eval();
			if (obj == nullptr) return nullptr;
			table->AddKey(obj, entry->key->Eval()->ToString() );
		}
	}
	
	return table;
}