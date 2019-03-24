#include "data/Fuse_Table.hpp"

using namespace Fuse;

Table::Table() { ; }

Type Fuse::Table::GetType() {
	return TYPE_TABLE;
}


std::string Fuse::Table::ToString() {
	std::string result = "";
	for (auto entry : data) {
		result += entry->ToString() + " ";
	}
	return result;
}

void Fuse::Table::AddEntry(Object* obj) {
	auto p = std::shared_ptr<Object> ( obj->Clone() );
	data.push_back( p );
}

std::size_t Fuse::Table::Count() {
	return data.size();
}

void Fuse::Table::AddKey(Object* obj, const std::string& key) {
	auto p = std::shared_ptr<Object> ( obj->Clone() );
	data.push_back( p );
	dict[key] = p;
}

std::shared_ptr<Object> Fuse::Table::Access(std::size_t index) {
	try {
		return data.at(index);
	} catch ( ... ) { return nullptr; }
}

std::shared_ptr<Object> Fuse::Table::Access(const std::string& key) {
	auto p = dict.find(key);
	if (p == dict.end()) return nullptr;
	return p->second;
}

int Fuse::Table::Erase(std::size_t index) {
	// check if out of bounds
	if (index >= data.size()) return 0;
	data.erase(data.begin() + index);
	return 1;
}

int Fuse::Table::Erase(const std::string& key) {
	auto it = dict.find(key);
	// find if it exists
	if (it == dict.end()) return 0;
	
	for (auto entry = data.begin(); entry != data.end(); ++entry) {
		if (it->second == *entry) {
			data.erase(entry);
			break;
		}
	}
	
	dict.erase(it);
	return 1;
}

Table* Fuse::Table::Clone() {
	auto t = new Table();
	
	for (auto entry : data) {
		t->AddEntry(entry.get());
		
		for (auto key : dict) {
			if (key.second == entry) {
				t->dict[key.first] = t->data.back();
				break;
			}
		}
	}
	
	return t;
}

bool Fuse::Table::IsTrue() {
	return !data.empty();
}