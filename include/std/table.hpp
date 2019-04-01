#pragma once

#include "Fuse_Funcs.hpp"

namespace Fuse {

std::shared_ptr<Object> _tableAt(std::vector<std::shared_ptr<Object>>& args); // table , index
std::shared_ptr<Object> _tableInsert(std::vector<std::shared_ptr<Object>>& args); // table , index , data
std::shared_ptr<Object> _tableMap(std::vector<std::shared_ptr<Object>>& args); // table , key , data
std::shared_ptr<Object> _tableDelete(std::vector<std::shared_ptr<Object>>& args); // table , index
std::shared_ptr<Object> _tableErase(std::vector<std::shared_ptr<Object>>& args); // table , key
std::shared_ptr<Object> _tableSize(std::vector<std::shared_ptr<Object>>& args); // table
std::shared_ptr<Object> _tableEmpty(std::vector<std::shared_ptr<Object>>& args); // table
std::shared_ptr<Object> _tableClear(std::vector<std::shared_ptr<Object>>& args); // table
std::shared_ptr<Object> _tablePush(std::vector<std::shared_ptr<Object>>& args); // table data
std::shared_ptr<Object> _tablePop(std::vector<std::shared_ptr<Object>>& args); // table
std::shared_ptr<Object> _tableLast(std::vector<std::shared_ptr<Object>>& args); // table
std::shared_ptr<Object> _tableFirst(std::vector<std::shared_ptr<Object>>& args); // table

};