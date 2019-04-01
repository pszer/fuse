#include "std/math.hpp"

using namespace Fuse;

std::shared_ptr<Object> Fuse::_mathSqrt(std::vector<std::shared_ptr<Object>>& args) // x
{
	return MakeNumber( std::sqrt(GetNumber(args.at(0))->Double()) );
}
std::shared_ptr<Object> Fuse::_mathCbrt(std::vector<std::shared_ptr<Object>>& args) // x
{
	return MakeNumber( std::cbrt(GetNumber(args.at(0))->Double()) );
}

std::shared_ptr<Object> Fuse::_mathCos(std::vector<std::shared_ptr<Object>>& args) // x
{
	return MakeNumber( std::cos(GetNumber(args.at(0))->Double()) );
}
std::shared_ptr<Object> Fuse::_mathSin(std::vector<std::shared_ptr<Object>>& args) // x
{
	return MakeNumber( std::sin(GetNumber(args.at(0))->Double()) );
}
std::shared_ptr<Object> Fuse::_mathTan(std::vector<std::shared_ptr<Object>>& args) // x
{
	return MakeNumber( std::tan(GetNumber(args.at(0))->Double()) );
}

std::shared_ptr<Object> Fuse::_mathAcos(std::vector<std::shared_ptr<Object>>& args) // x
{
	return MakeNumber( std::acos(GetNumber(args.at(0))->Double()) );
}
std::shared_ptr<Object> Fuse::_mathAsin(std::vector<std::shared_ptr<Object>>& args) // x
{
	return MakeNumber( std::asin(GetNumber(args.at(0))->Double()) );
}
std::shared_ptr<Object> Fuse::_mathAtan(std::vector<std::shared_ptr<Object>>& args) // x
{
	return MakeNumber( std::atan(GetNumber(args.at(0))->Double()) );
}
std::shared_ptr<Object> Fuse::_mathAtan2(std::vector<std::shared_ptr<Object>>& args) // x y
{
	return MakeNumber( std::atan2(GetNumber(args.at(0))->Double(), GetNumber(args.at(1))->Double()) );
}

std::shared_ptr<Object> Fuse::_mathCosh(std::vector<std::shared_ptr<Object>>& args) // x
{
	return MakeNumber( std::cosh(GetNumber(args.at(0))->Double()) );
}
std::shared_ptr<Object> Fuse::_mathSinh(std::vector<std::shared_ptr<Object>>& args) // x
{
	return MakeNumber( std::sinh(GetNumber(args.at(0))->Double()) );
}
std::shared_ptr<Object> Fuse::_mathTanh(std::vector<std::shared_ptr<Object>>& args) // x
{
	return MakeNumber( std::tanh(GetNumber(args.at(0))->Double()) );
}

std::shared_ptr<Object> Fuse::_mathExp(std::vector<std::shared_ptr<Object>>& args) // x
{
	return MakeNumber( std::exp(GetNumber(args.at(0))->Double()) );
}
std::shared_ptr<Object> Fuse::_mathLog(std::vector<std::shared_ptr<Object>>& args) // x
{
	return MakeNumber( std::log(GetNumber(args.at(0))->Double()) );
}
std::shared_ptr<Object> Fuse::_mathLog10(std::vector<std::shared_ptr<Object>>& args) // x
{
	return MakeNumber( std::log10(GetNumber(args.at(0))->Double()) );
}

std::shared_ptr<Object> Fuse::_mathCeiling(std::vector<std::shared_ptr<Object>>& args) // x
{
	return MakeNumber( std::ceil(GetNumber(args.at(0))->Double()) );
}
std::shared_ptr<Object> Fuse::_mathFloor(std::vector<std::shared_ptr<Object>>& args) // x
{
	return MakeNumber( std::floor(GetNumber(args.at(0))->Double()) );
}