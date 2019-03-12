#include "Operations.hpp"

using namespace Fuse;

std::map< unsigned int, Operation_Func> Fuse::Operations;

unsigned int Fuse::OpDef(Type _LHS, Type _RHS, OPERATORS _Op) {
	unsigned int result = 0x0;
	result += _LHS << 16;
	result += _RHS << 8;
	result += _Op;
}

Operation_Func Fuse::GetOperation(Type a, Type b, OPERATORS op) {
	auto o = Operations.find(OpDef(a, b, op));
	if (o == Operations.end()) {
		return nullptr;
	}
}

std::shared_ptr<Object> Fuse::DoOperation(std::shared_ptr<Object> a, std::shared_ptr<Object> b, OPERATORS op) {
	auto func = GetOperation(a->GetType(), b->GetType(), op);
	if (func == nullptr) return nullptr;
	
	return (*func)(a, b);
}

std::shared_ptr<Object> Fuse::__Num_Num_Add__(std::shared_ptr<Object> a,std::shared_ptr<Object> b) {
	Number* num_a = (Number*)a.get(), *num_b = (Number*)b.get();
	
	if (num_a->GetNum().type == INT) {
		if (num_b->GetNum().type == INT) {
			return std::make_shared<Number>(num_a->GetNum().INT + num_b->GetNum().INT);
		} else {
			return std::make_shared<Number>((double)num_a->GetNum().INT + num_b->GetNum().DOUBLE);
		}
	} else {
		if (num_b->GetNum().type == INT) {
			return std::make_shared<Number>(num_a->GetNum().DOUBLE + (double)num_b->GetNum().INT);
		} else {
			return std::make_shared<Number>(num_a->GetNum().DOUBLE + num_b->GetNum().DOUBLE);
		}
	}
}

std::shared_ptr<Object> Fuse::__Num_Num_Sub__(std::shared_ptr<Object> a,std::shared_ptr<Object> b) {
	Number* num_a = (Number*)a.get(), *num_b = (Number*)b.get();
	
	if (num_a->GetNum().type == INT) {
		if (num_b->GetNum().type == INT) {
			return std::make_shared<Number>(num_a->GetNum().INT - num_b->GetNum().INT);
		} else {
			return std::make_shared<Number>((double)num_a->GetNum().INT - num_b->GetNum().DOUBLE);
		}
	} else {
		if (num_b->GetNum().type == INT) {
			return std::make_shared<Number>(num_a->GetNum().DOUBLE - (double)num_b->GetNum().INT);
		} else {
			return std::make_shared<Number>(num_a->GetNum().DOUBLE - num_b->GetNum().DOUBLE);
		}
	}
}

void Fuse::InitOperations() {
	auto func = &Fuse::__Num_Num_Add__;
	Operations[ OpDef(TYPE_NUMBER, TYPE_NUMBER, OP_ADD) ] = (Operation_Func)100;
	std::cout << "nice" << std::endl;
	Operations[ OpDef(TYPE_NUMBER, TYPE_NUMBER, OP_SUB) ] = &Fuse::__Num_Num_Sub__;
	std::cout << "nice" << std::endl;
}