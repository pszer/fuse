#include "std/table.hpp"

using namespace Fuse;

std::shared_ptr<Object> Fuse::_tableAt(std::vector<std::shared_ptr<Object>>& args) { // table , index
	auto table = GetTable(args.at(0));
	auto index = GetNumber(args.at(1))->Int();
	
	if (index < 0 || index >= table->Count()) {
		Core.SetErrorMessage("index [" + std::to_string(index) + "] out of range");
		return NullReturn();
	}
	
	return table->Access(index);
}

std::shared_ptr<Object> Fuse::_tableInsert(std::vector<std::shared_ptr<Object>>& args) { // table , index , data
	auto table = GetTable(args.at(0));
	auto index = GetNumber(args.at(1))->Int();
	
	if (index < 0) {
		Core.SetErrorMessage("index [" + std::to_string(index) + "] is negative");
		return NullReturn();
	}
	
	return table->Assign(index, args.at(2));
}

std::shared_ptr<Object> Fuse::_tableMap(std::vector<std::shared_ptr<Object>>& args) { // table , key , data
	auto table = GetTable(args.at(0));
	auto key = GetString(args.at(1))->Str();
	
	return table->Assign(key, args.at(2));
}

std::shared_ptr<Object> Fuse::_tableDelete(std::vector<std::shared_ptr<Object>>& args) { // table , index
	auto table = GetTable(args.at(0));
	auto index = GetNumber(args.at(1))->Int();
	
	if (index < 0 || index >= table->Count()) {
		Core.SetErrorMessage("trying to delete index [" + std::to_string(index) + "] which is out of range");
		return NullReturn();
	}
	
	table->Erase(index);
	return NullReturn();
}

std::shared_ptr<Object> Fuse::_tableErase(std::vector<std::shared_ptr<Object>>& args) { // table , key
	auto table = GetTable(args.at(0));
	auto key = GetString(args.at(1))->Str();
	
	table->Erase(key);
	
	return NullReturn();
}

std::shared_ptr<Object> Fuse::_tableSize(std::vector<std::shared_ptr<Object>>& args) { // table
	auto table = GetTable(args.at(0));
	return MakeNumber((long long)table->Count());
}

std::shared_ptr<Object> Fuse::_tableEmpty(std::vector<std::shared_ptr<Object>>& args) { // table
	auto table = GetTable(args.at(0));
	return MakeBool(table->Count() == 0);
}

std::shared_ptr<Object> Fuse::_tableClear(std::vector<std::shared_ptr<Object>>& args) { // table
	auto table = GetTable(args.at(0));
	table->Clear();
	return NullReturn();
}

std::shared_ptr<Object> Fuse::_tablePush(std::vector<std::shared_ptr<Object>>& args) { // table data
	auto table = GetTable(args.at(0));
	return table->Push(args.at(1));
}

std::shared_ptr<Object> Fuse::_tablePop(std::vector<std::shared_ptr<Object>>& args) { // table
	auto table = GetTable(args.at(0));
	auto popped = table->Pop();
	if (popped == nullptr) {
		Core.SetErrorMessage("trying to pop an empty table");
		return NullReturn();
	}
	
	return popped;
}

std::shared_ptr<Object> Fuse::_tableFirst(std::vector<std::shared_ptr<Object>>& args) { // table
	auto table = GetTable(args.at(0));
	if (table->Count() == 0) {
		Core.SetErrorMessage("trying to access empty table (using table.First())");
		return NullReturn();
	}
	return table->Access(0);
}

std::shared_ptr<Object> Fuse::_tableLast(std::vector<std::shared_ptr<Object>>& args) { // table
	auto table = GetTable(args.at(0));
	if (table->Count() == 0) {
		Core.SetErrorMessage("trying to access empty table (using table.Last())");
		return NullReturn();
	}
	return table->Access(table->Count()-1);
}