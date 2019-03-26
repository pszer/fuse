#include "data/Fuse_Table.hpp"
#include "Fuse_Core.hpp"

using namespace Fuse;

Table::Table() { ; }

Type Fuse::Table::GetType() {
	return TYPE_TABLE;
}


std::string Fuse::Table::ToString() {
	std::string result = "";
	for (auto entry : data) {
		result += (*entry)->ToString() + " ";
	}
	return result;
}

void Fuse::Table::AddEntry(std::shared_ptr<Object> obj) {
	auto p =  std::make_shared<std::shared_ptr<Object>>(obj->Clone());
	data.push_back( p );
}

std::size_t Fuse::Table::Count() {
	return data.size();
}

void Fuse::Table::AddKey(std::shared_ptr<Object> obj, const std::string& key) {
	auto p = std::make_shared<std::shared_ptr<Object>>(obj->Clone());
	data.push_back( p );
	dict[key] = p;
}

std::shared_ptr<Fuse::Object> Fuse::Table::Access(std::size_t index) {
	if (data.size() > index) {
		return *data.at(index);
	} else {
		Core.SetErrorMessage("index [" + std::to_string(index) + "] is out of bounds.");
		return nullptr;
	}
}

std::shared_ptr<Fuse::Object> Fuse::Table::Access(const std::string& key) {
	auto p = dict.find(key);
	if (p == dict.end()) {
		Core.SetErrorMessage("table key \"" + key + "\" doesn't exist");
		return nullptr;
	}
	return *p->second;
}

std::shared_ptr<Fuse::Object> Fuse::Table::Assign(std::size_t index, std::shared_ptr<Object> obj) {
	if (data.size() > index) {
		*data.at(index) = obj;
	} else {
		int I = index - data.size();
		for (long long i = 0; i <= I; ++i) {
			data.push_back(std::make_shared<std::shared_ptr<Object>>(std::make_shared<Null>()));
		}
		
		*data.at(index) = obj;
	}
	
	return obj;
}

std::shared_ptr<Fuse::Object> Fuse::Table::Assign(const std::string& key, std::shared_ptr<Object> obj) {
	auto p = dict.find(key);
	if (p == dict.end()) {
		AddKey(std::make_shared<Null>(), key);
		*dict.find(key)->second = obj;
	}
	*p->second = obj;
	
	return obj;
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

std::shared_ptr<Object> Fuse::Table::Clone() {
	auto t = std::make_shared<Table>();
	
	for (auto entry : data) {
		t->AddEntry(*entry);
		
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