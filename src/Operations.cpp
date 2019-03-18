#include "Operations.hpp"
#include "Fuse_Core.hpp"

using namespace Fuse;

//static std::vector<Operation> Fuse::Operations[OP_COUNT];
//std::vector<Operation> Fuse::Operations[OP_COUNT];

Operation_Func Fuse::GetOperation(Type a, Type b, OPERATORS op) {
	for (auto entry : Core.Operations[(int)op]) {
		if (entry.a == a && entry.b == b) {
			return entry.func;
		}
	}
	
	return nullptr;
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

std::shared_ptr<Object> Fuse::__Num_Num_Mult__(std::shared_ptr<Object> a,std::shared_ptr<Object> b) {
	Number* num_a = (Number*)a.get(), *num_b = (Number*)b.get();
	
	if (num_a->GetNum().type == INT) {
		if (num_b->GetNum().type == INT) {
			return std::make_shared<Number>(num_a->GetNum().INT * num_b->GetNum().INT);
		} else {
			return std::make_shared<Number>((double)num_a->GetNum().INT * num_b->GetNum().DOUBLE);
		}
	} else {
		if (num_b->GetNum().type == INT) {
			return std::make_shared<Number>(num_a->GetNum().DOUBLE * (double)num_b->GetNum().INT);
		} else {
			return std::make_shared<Number>(num_a->GetNum().DOUBLE * num_b->GetNum().DOUBLE);
		}
	}
}

std::shared_ptr<Object> Fuse::__Num_Num_Div__(std::shared_ptr<Object> a,std::shared_ptr<Object> b) {
	Number* num_a = (Number*)a.get(), *num_b = (Number*)b.get();
	
	if (num_a->GetNum().type == INT) {
		if (num_b->GetNum().type == INT) {
			auto remainder = num_a->GetNum().INT % num_b->GetNum().INT;
			if (!remainder)
				return std::make_shared<Number>(num_a->GetNum().INT / num_b->GetNum().INT);
			else
				return std::make_shared<Number>(num_a->GetNum().INT / (double)num_b->GetNum().INT);
		} else {
			return std::make_shared<Number>((double)num_a->GetNum().INT / num_b->GetNum().DOUBLE);
		}
	} else {
		if (num_b->GetNum().type == INT) {
			return std::make_shared<Number>(num_a->GetNum().DOUBLE / (double)num_b->GetNum().INT);
		} else {
			return std::make_shared<Number>(num_a->GetNum().DOUBLE / num_b->GetNum().DOUBLE);
		}
	}
}

void Fuse::InitOperations() {
	Core.Operations[OP_ADD] .push_back(Operation(TYPE_NUMBER, TYPE_NUMBER, __Num_Num_Add__));
	Core.Operations[OP_SUB] .push_back(Operation(TYPE_NUMBER, TYPE_NUMBER, __Num_Num_Sub__));
	Core.Operations[OP_MULT].push_back(Operation(TYPE_NUMBER, TYPE_NUMBER, __Num_Num_Mult__));
	Core.Operations[OP_DIV] .push_back(Operation(TYPE_NUMBER, TYPE_NUMBER, __Num_Num_Div__));
}