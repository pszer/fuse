#pragma once

#include "Fuse_Funcs.hpp"

namespace Fuse {

std::shared_ptr<Object> _ioConsolePrint(std::vector<std::shared_ptr<Object>>& args);
std::shared_ptr<Object> _ioConsoleGetChar(std::vector<std::shared_ptr<Object>>& args);
std::shared_ptr<Object> _ioConsoleGetLine(std::vector<std::shared_ptr<Object>>& args);

};