#pragma once

#include <cmath>
#include <memory>

#include "Fuse_Funcs.hpp"

namespace Fuse {

std::shared_ptr<Object> _mathSqrt(std::vector<std::shared_ptr<Object>>& args); // x
std::shared_ptr<Object> _mathCbrt(std::vector<std::shared_ptr<Object>>& args); // x

std::shared_ptr<Object> _mathCos(std::vector<std::shared_ptr<Object>>& args); // x
std::shared_ptr<Object> _mathSin(std::vector<std::shared_ptr<Object>>& args); // x
std::shared_ptr<Object> _mathTan(std::vector<std::shared_ptr<Object>>& args); // x

std::shared_ptr<Object> _mathAcos(std::vector<std::shared_ptr<Object>>& args); // x
std::shared_ptr<Object> _mathAsin(std::vector<std::shared_ptr<Object>>& args); // x
std::shared_ptr<Object> _mathAtan(std::vector<std::shared_ptr<Object>>& args); // x
std::shared_ptr<Object> _mathAtan2(std::vector<std::shared_ptr<Object>>& args); // x y

std::shared_ptr<Object> _mathCosh(std::vector<std::shared_ptr<Object>>& args); // x
std::shared_ptr<Object> _mathSinh(std::vector<std::shared_ptr<Object>>& args); // x
std::shared_ptr<Object> _mathTanh(std::vector<std::shared_ptr<Object>>& args); // x

std::shared_ptr<Object> _mathExp(std::vector<std::shared_ptr<Object>>& args); // x
std::shared_ptr<Object> _mathLog(std::vector<std::shared_ptr<Object>>& args); // x
std::shared_ptr<Object> _mathLog10(std::vector<std::shared_ptr<Object>>& args); // x

std::shared_ptr<Object> _mathCeiling(std::vector<std::shared_ptr<Object>>& args); // x
std::shared_ptr<Object> _mathFloor(std::vector<std::shared_ptr<Object>>& args); // x

};