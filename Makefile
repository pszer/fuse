IDIR =include
CC=g++
CFLAGS=-I$(IDIR) -std=c++1z -O3

ODIR=src/obj
SDIR=src
LDIR =../lib

LIBS=-lm -lpthread

_DEPS = data/Fuse_Object.hpp data/Fuse_Table.hpp data/Fuse_Number.hpp data/Fuse_String.hpp data/Fuse_Bool.hpp data/Fuse_Function.hpp Fuse_Core.hpp Lexer.hpp \
Parser.hpp AST.hpp ast/Base.hpp ast/Literals.hpp ast/Block.hpp ast/FuncDef.hpp ast/Object.hpp ast/Variable.hpp ast/BinaryExpr.hpp Variable.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o Fuse_Core.o Lexer.o Parser.o ast/FuncDef.o ast/Object.o ast/Variable.o ast/BinaryExpr.o data/Fuse_Object.o data/Fuse_Table.o data/Fuse_Number.o \
data/Fuse_String.o data/Fuse_Bool.o data/Fuse_Function.o ast/Base.o ast/Literals.o ast/Block.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

OUTPUT = fuse-test

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
make: $(OBJ)
	$(CC) -o $(OUTPUT) $^ $(CFLAGS) $(LIBS)
	
debug: $(OBJ)
	$(CC) -g -o $(OUTPUT) $^ $(CFLAGS) $(LIBS) 

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
