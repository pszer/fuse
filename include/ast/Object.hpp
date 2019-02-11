#pragma once

#include "ast/Base.hpp"

namespace Fuse {
	
	class ObjectAST : public ExprAST {
	public:
		ObjectAST(std::shared_ptr<Fuse::Object> _obj): Obj(_obj) { ; }
		
		// Eval and GetObject are synonymous
		std::shared_ptr<Fuse::Object> Eval();
		std::shared_ptr<Fuse::Object> GetObject();
		Type GetObjType();
	private:
		std::shared_ptr<Fuse::Object> Obj;
		TypeAST type = NODE_OBJECT;
	};
	
};