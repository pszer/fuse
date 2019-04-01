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

UnaryOperation_Func Fuse::GetUnaryOperation(Type type, POSTUNARY_OPERATORS op) {
	for (auto entry : Core.PostUnopOperations[(int)op]) {
		if (entry.type == type) {
			return entry.func;
		}
	}
}

UnaryOperation_Func Fuse::GetUnaryOperation(Type type, PREUNARY_OPERATORS op) {
	for (auto entry : Core.PreUnopOperations[(int)op]) {
		if (entry.type == type) {
			return entry.func;
		}
	}
}

std::shared_ptr<Object> Fuse::DoOperation(std::shared_ptr<Object> a, std::shared_ptr<Object> b, OPERATORS op) {
	auto func = GetOperation(a->GetType(), b->GetType(), op);
	if (func == nullptr) return nullptr;
	
	return (*func)(a, b);
}

std::shared_ptr<Object> Fuse::DoOperation(std::shared_ptr<Object> a, POSTUNARY_OPERATORS op) {
	auto func = GetUnaryOperation(a->GetType(), op);
	if (func == nullptr) return nullptr;
	
	return (*func)(a);
}

std::shared_ptr<Object> Fuse::DoOperation(std::shared_ptr<Object> a, PREUNARY_OPERATORS op) {
	auto func = GetUnaryOperation(a->GetType(), op);
	if (func == nullptr) return nullptr;
	
	return (*func)(a);
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

std::shared_ptr<Object> Fuse::__Num_Num_Mod__(std::shared_ptr<Object> a,std::shared_ptr<Object> b) {
	Number* num_a = (Number*)a.get(), *num_b = (Number*)b.get();
	
	if (num_a->GetNum().type == INT) {
		if (num_b->GetNum().type == INT) {
			return std::make_shared<Number>(num_a->GetNum().INT % num_b->GetNum().INT);
		} else {
			return std::make_shared<Number>(std::fmod( (double)num_a->GetNum().INT, num_b->GetNum().DOUBLE) );
		}
	} else {
		if (num_b->GetNum().type == INT) {
			return std::make_shared<Number>(std::fmod( num_a->GetNum().DOUBLE, (double)num_b->GetNum().INT) );
		} else {
			return std::make_shared<Number>(std::fmod(num_a->GetNum().DOUBLE, num_b->GetNum().DOUBLE) );
		}
	}
}

std::shared_ptr<Object> Fuse::__Num_Num_Equal__(std::shared_ptr<Object> a,std::shared_ptr<Object> b) {
	Number* num_a = (Number*)a.get(), *num_b = (Number*)b.get();
	if (num_a->GetNum().type == INT && num_b->GetNum().type == INT) {
		return std::make_shared<Bool>(num_a->GetNum().INT == num_b->GetNum().INT);
	} else {
		return std::make_shared<Bool>(
			(num_a->GetNum().type == DOUBLE ? num_a->GetNum().DOUBLE : (double)num_a->GetNum().INT)
			==
			(num_b->GetNum().type == DOUBLE ? num_b->GetNum().DOUBLE : (double)num_b->GetNum().INT));
	}
}

std::shared_ptr<Object> Fuse::__Num_Num_Unequal__(std::shared_ptr<Object> a,std::shared_ptr<Object> b) {
	Number* num_a = (Number*)a.get(), *num_b = (Number*)b.get();
	if (num_a->GetNum().type == INT && num_b->GetNum().type == INT) {
		return std::make_shared<Bool>(num_a->GetNum().INT != num_b->GetNum().INT);
	} else {
		return std::make_shared<Bool>(
			(num_a->GetNum().type == DOUBLE ? num_a->GetNum().DOUBLE : (double)num_a->GetNum().INT)
			!=
			(num_b->GetNum().type == DOUBLE ? num_b->GetNum().DOUBLE : (double)num_b->GetNum().INT));
	}
}

std::shared_ptr<Object> Fuse::__Num_Num_Less__(std::shared_ptr<Object> a,std::shared_ptr<Object> b) {
	Number* num_a = (Number*)a.get(), *num_b = (Number*)b.get();
	if (num_a->GetNum().type == INT && num_b->GetNum().type == INT) {
		return std::make_shared<Bool>(num_a->GetNum().INT < num_b->GetNum().INT);
	} else {
		return std::make_shared<Bool>(
			(num_a->GetNum().type == DOUBLE ? num_a->GetNum().DOUBLE : (double)num_a->GetNum().INT)
			<
			(num_b->GetNum().type == DOUBLE ? num_b->GetNum().DOUBLE : (double)num_b->GetNum().INT));
	}
}

std::shared_ptr<Object> Fuse::__Num_Num_Greater__(std::shared_ptr<Object> a,std::shared_ptr<Object> b) {
	Number* num_a = (Number*)a.get(), *num_b = (Number*)b.get();
	if (num_a->GetNum().type == INT && num_b->GetNum().type == INT) {
		return std::make_shared<Bool>(num_a->GetNum().INT > num_b->GetNum().INT);
	} else {
		return std::make_shared<Bool>(
			(num_a->GetNum().type == DOUBLE ? num_a->GetNum().DOUBLE : (double)num_a->GetNum().INT)
			>
			(num_b->GetNum().type == DOUBLE ? num_b->GetNum().DOUBLE : (double)num_b->GetNum().INT));
	}
}

std::shared_ptr<Object> Fuse::__Num_Num_EqLess__(std::shared_ptr<Object> a,std::shared_ptr<Object> b) {
	Number* num_a = (Number*)a.get(), *num_b = (Number*)b.get();
	if (num_a->GetNum().type == INT && num_b->GetNum().type == INT) {
		return std::make_shared<Bool>(num_a->GetNum().INT <= num_b->GetNum().INT);
	} else {
		return std::make_shared<Bool>(
			(num_a->GetNum().type == DOUBLE ? num_a->GetNum().DOUBLE : (double)num_a->GetNum().INT)
			<=
			(num_b->GetNum().type == DOUBLE ? num_b->GetNum().DOUBLE : (double)num_b->GetNum().INT));
	}
}

std::shared_ptr<Object> Fuse::__Num_Num_EqGreater__(std::shared_ptr<Object> a,std::shared_ptr<Object> b) {
	Number* num_a = (Number*)a.get(), *num_b = (Number*)b.get();
	if (num_a->GetNum().type == INT && num_b->GetNum().type == INT) {
		return std::make_shared<Bool>(num_a->GetNum().INT >= num_b->GetNum().INT);
	} else {
		return std::make_shared<Bool>(
			(num_a->GetNum().type == DOUBLE ? num_a->GetNum().DOUBLE : (double)num_a->GetNum().INT)
			>=
			(num_b->GetNum().type == DOUBLE ? num_b->GetNum().DOUBLE : (double)num_b->GetNum().INT));
	}
}

std::shared_ptr<Object> Fuse::__Num_Num_And__(std::shared_ptr<Object> a,std::shared_ptr<Object> b) {
	Number* num_a = (Number*)a.get(), *num_b = (Number*)b.get();
	if (num_a->GetNum().type == INT && num_b->GetNum().type == INT) {
		return std::make_shared<Bool>(num_a->GetNum().INT && num_b->GetNum().INT);
	} else {
		return std::make_shared<Bool>(
			(num_a->GetNum().type == DOUBLE ? num_a->GetNum().DOUBLE : (double)num_a->GetNum().INT)
			&&
			(num_b->GetNum().type == DOUBLE ? num_b->GetNum().DOUBLE : (double)num_b->GetNum().INT));
	}
}

std::shared_ptr<Object> Fuse::__Num_Num_Or__(std::shared_ptr<Object> a,std::shared_ptr<Object> b) {
	Number* num_a = (Number*)a.get(), *num_b = (Number*)b.get();
	if (num_a->GetNum().type == INT && num_b->GetNum().type == INT) {
		return std::make_shared<Bool>(num_a->GetNum().INT || num_b->GetNum().INT);
	} else {
		return std::make_shared<Bool>(
			(num_a->GetNum().type == DOUBLE ? num_a->GetNum().DOUBLE : (double)num_a->GetNum().INT)
			||
			(num_b->GetNum().type == DOUBLE ? num_b->GetNum().DOUBLE : (double)num_b->GetNum().INT));
	}
}

std::shared_ptr<Object> Fuse::__Bool_Bool_Equal__(std::shared_ptr<Object> a,std::shared_ptr<Object> b) {
	return std::make_shared<Bool>(a->IsTrue() == b->IsTrue());
}

std::shared_ptr<Object> Fuse::__Bool_Bool_Unequal__(std::shared_ptr<Object> a,std::shared_ptr<Object> b) {
	return std::make_shared<Bool>(a->IsTrue() != b->IsTrue());
}

std::shared_ptr<Object> Fuse::__Bool_Bool_And__(std::shared_ptr<Object> a,std::shared_ptr<Object> b) {
	return std::make_shared<Bool>(a->IsTrue() && b->IsTrue());
}

std::shared_ptr<Object> Fuse::__Bool_Bool_Or__(std::shared_ptr<Object> a,std::shared_ptr<Object> b) {
	return std::make_shared<Bool>(a->IsTrue() || b->IsTrue());
}

std::shared_ptr<Object> Fuse::__Str_Str_Equal__(std::shared_ptr<Object> a,std::shared_ptr<Object> b) {
	return std::make_shared<Bool>(a->ToString() == b->ToString());
}

std::shared_ptr<Object> Fuse::__Str_Str_Unequal__(std::shared_ptr<Object> a,std::shared_ptr<Object> b) {
	return std::make_shared<Bool>(a->ToString() != b->ToString());
}

std::shared_ptr<Object> Fuse::__Str_Str_Add__(std::shared_ptr<Object> a,std::shared_ptr<Object> b) {
	return std::make_shared<String>(a->ToString() + b->ToString());
}

std::shared_ptr<Object> Fuse::__Str_Num_Add__(std::shared_ptr<Object> a,std::shared_ptr<Object> b) {
	return std::make_shared<String>(a->ToString() + b->ToString());
}

std::shared_ptr<Object> Fuse::__Num_Str_Add__(std::shared_ptr<Object> a,std::shared_ptr<Object> b) {
	return std::make_shared<String>(a->ToString() + b->ToString());
}

std::shared_ptr<Object> Fuse::__Str_Bool_Add__(std::shared_ptr<Object> a,std::shared_ptr<Object> b) {
	return std::make_shared<String>(a->ToString() + b->ToString());
}

std::shared_ptr<Object> Fuse::__Bool_Str_Add__(std::shared_ptr<Object> a,std::shared_ptr<Object> b) {
	return std::make_shared<String>(a->ToString() + b->ToString());
}

std::shared_ptr<Object> Fuse::__Pre_Inc__(std::shared_ptr<Object> a) {
	if (GetNumber(a)->GetNum().type == INT) {
		GetNumber(a)->GetNum().INT++;
		return a;
	} else {
		GetNumber(a)->GetNum().DOUBLE += 1.0;
		return a;
	}
}
std::shared_ptr<Object> Fuse::__Pre_Dec__(std::shared_ptr<Object> a) {
	if (GetNumber(a)->GetNum().type == INT) {
		GetNumber(a)->GetNum().INT--;
		return MakeNumber(GetNumber(a)->Int());
	} else {
		GetNumber(a)->GetNum().DOUBLE -= 1.0;
		return MakeNumber(GetNumber(a)->GetNum().DOUBLE);
	}
}

std::shared_ptr<Object> Fuse::__Pre_Bool_Not__(std::shared_ptr<Object> a) {
	return MakeBool(!GetBool(a)->Value());
}

std::shared_ptr<Object> Fuse::__Pre_Number_Not__(std::shared_ptr<Object> a) {
	return MakeBool(!a->IsTrue());
}
std::shared_ptr<Object> Fuse::__Pre_Number_Negate__(std::shared_ptr<Object> a) {
	if (GetNumber(a)->GetNum().type == INT) {
		return MakeNumber(-GetNumber(a)->GetNum().INT);
	} else {
		return MakeNumber(-GetNumber(a)->GetNum().DOUBLE);
	}
}
	
std::shared_ptr<Object> Fuse::__Post_Inc__(std::shared_ptr<Object> a) {
	if (GetNumber(a)->GetNum().type == INT) {
		long long _int = GetNumber(a)->GetNum().INT;
		GetNumber(a)->GetNum().INT++;
		return MakeNumber(_int);
	} else {
		double _double = GetNumber(a)->GetNum().DOUBLE;
		GetNumber(a)->GetNum().DOUBLE += 1.0;
		return MakeNumber(_double);
	}
}
std::shared_ptr<Object> Fuse::__Post_Dec__(std::shared_ptr<Object> a) {
	if (GetNumber(a)->GetNum().type == INT) {
		auto _int = GetNumber(a)->GetNum().INT;
		GetNumber(a)->GetNum().INT--;
		return MakeNumber(_int);
	} else {
		auto _double = GetNumber(a)->GetNum().DOUBLE;
		GetNumber(a)->GetNum().DOUBLE -= 1.0;
		return MakeNumber(_double);
	}
}

void Fuse::InitOperations() {
	Core.Operations[OP_ADD] .push_back(Operation(TYPE_NUMBER, TYPE_NUMBER, __Num_Num_Add__));
	Core.Operations[OP_SUB] .push_back(Operation(TYPE_NUMBER, TYPE_NUMBER, __Num_Num_Sub__));
	Core.Operations[OP_MULT].push_back(Operation(TYPE_NUMBER, TYPE_NUMBER, __Num_Num_Mult__));
	Core.Operations[OP_DIV] .push_back(Operation(TYPE_NUMBER, TYPE_NUMBER, __Num_Num_Div__));
	Core.Operations[OP_MODULO].push_back(Operation(TYPE_NUMBER, TYPE_NUMBER, __Num_Num_Mod__));
	
	Core.Operations[OP_COMP_EQUAL].push_back(Operation(TYPE_NUMBER, TYPE_NUMBER, __Num_Num_Equal__));
	Core.Operations[OP_COMP_UNEQUAL].push_back(Operation(TYPE_NUMBER, TYPE_NUMBER, __Num_Num_Unequal__));
	Core.Operations[OP_COMP_LESS].push_back(Operation(TYPE_NUMBER, TYPE_NUMBER, __Num_Num_Less__));
	Core.Operations[OP_COMP_GREATER].push_back(Operation(TYPE_NUMBER, TYPE_NUMBER, __Num_Num_Greater__));
	Core.Operations[OP_COMP_LESS_EQUAL].push_back(Operation(TYPE_NUMBER, TYPE_NUMBER, __Num_Num_EqLess__));
	Core.Operations[OP_COMP_GREATER_EQUAL].push_back(Operation(TYPE_NUMBER, TYPE_NUMBER, __Num_Num_EqGreater__));
	Core.Operations[OP_AND].push_back(Operation(TYPE_NUMBER, TYPE_NUMBER, __Num_Num_And__));
	Core.Operations[OP_OR].push_back(Operation(TYPE_NUMBER, TYPE_NUMBER, __Num_Num_Or__));
	
	Core.Operations[OP_COMP_EQUAL].push_back(Operation(TYPE_BOOL, TYPE_BOOL, __Bool_Bool_Equal__));
	Core.Operations[OP_COMP_UNEQUAL].push_back(Operation(TYPE_BOOL, TYPE_BOOL, __Bool_Bool_Unequal__));
	Core.Operations[OP_AND].push_back(Operation(TYPE_BOOL, TYPE_BOOL, __Bool_Bool_And__));
	Core.Operations[OP_OR].push_back(Operation(TYPE_BOOL, TYPE_BOOL, __Bool_Bool_Or__));
	
	Core.Operations[OP_COMP_EQUAL].push_back(Operation(TYPE_STRING, TYPE_STRING, __Str_Str_Equal__));
	Core.Operations[OP_COMP_UNEQUAL].push_back(Operation(TYPE_STRING, TYPE_STRING, __Str_Str_Unequal__));
	Core.Operations[OP_ADD].push_back(Operation(TYPE_STRING, TYPE_STRING, __Str_Str_Add__));
	Core.Operations[OP_ADD].push_back(Operation(TYPE_STRING, TYPE_NUMBER, __Str_Num_Add__));
	Core.Operations[OP_ADD].push_back(Operation(TYPE_NUMBER, TYPE_STRING, __Num_Str_Add__));
	Core.Operations[OP_ADD].push_back(Operation(TYPE_STRING, TYPE_BOOL, __Str_Bool_Add__));
	Core.Operations[OP_ADD].push_back(Operation(TYPE_BOOL, TYPE_STRING, __Bool_Str_Add__));
	
	Core.PreUnopOperations[PRE_OP_INC].push_back(UnaryOperation(TYPE_NUMBER, __Pre_Inc__));
	Core.PreUnopOperations[PRE_OP_DEC].push_back(UnaryOperation(TYPE_NUMBER, __Pre_Dec__));
	Core.PreUnopOperations[PRE_OP_NOT].push_back(UnaryOperation(TYPE_NUMBER, __Pre_Number_Not__));
	Core.PreUnopOperations[PRE_OP_NOT].push_back(UnaryOperation(TYPE_BOOL, __Pre_Bool_Not__));
	Core.PreUnopOperations[PRE_OP_NEGATE].push_back(UnaryOperation(TYPE_NUMBER, __Pre_Number_Negate__));
	
	Core.PostUnopOperations[POST_OP_INC].push_back(UnaryOperation(TYPE_NUMBER, __Post_Inc__));
	Core.PostUnopOperations[POST_OP_DEC].push_back(UnaryOperation(TYPE_NUMBER, __Post_Dec__));
}