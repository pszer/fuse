#include "std/io.hpp"

using namespace Fuse;

std::shared_ptr<Object> Fuse::_ioConsolePrint(std::vector<std::shared_ptr<Object>>& args) {
	*Core._Lexer.ostream << args.at(0)->ToString() << std::endl;
	return NullReturn();
}

std::shared_ptr<Object> Fuse::_ioConsoleGetChar(std::vector<std::shared_ptr<Object>>& args) {
	if (Core.iconsole == nullptr) return NullReturn();
	return MakeString( std::string(1, (char)Core.iconsole->get()) );
}

std::shared_ptr<Object> Fuse::_ioConsoleGetLine(std::vector<std::shared_ptr<Object>>& args) {
	if (Core.iconsole == nullptr) return NullReturn();
	std::string str;
	std::getline(*Core.iconsole, str);
	return MakeString(str);
}
