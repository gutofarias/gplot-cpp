# -*- Makefile -*-


NAME 	= gplot

OBJ 	= ./obj
LIB 	= ./lib
DYLIB	= ./dylib
BIN 	= ./bin
OUTPUT	= ./output

CC	= g++



.PHONY: obj lib static-app static dylib dynamic-app dynamic run-static run-dynamic clean install uninstall



obj:
	mkdir -p $(OBJ)
	$(CC) -c $(NAME).cpp -I . -o $(OBJ)/$(NAME).o


lib:
	mkdir -p $(LIB)
	ar -rcs $(LIB)/lib$(NAME).a $(OBJ)/$(NAME).o


static-app:
	mkdir -p $(BIN)
	$(CC) $(NAME)-test.cpp -l$(NAME) -L $(LIB) -I . -o $(BIN)/$(NAME)-test-static


static: obj lib static-app


dylib:
	mkdir -p $(DYLIB)
	$(CC) -dynamiclib $(NAME).cpp -I . -o $(DYLIB)/lib$(NAME).dylib


dynamic-app:
	mkdir -p $(BIN)
	$(CC) $(NAME)-test.cpp $(DYLIB)/lib$(NAME).dylib -I . -o $(BIN)/$(NAME)-test-dynamic


dynamic: dylib dynamic-app


run-static:
	mkdir -p $(OUTPUT)
	$(BIN)/$(NAME)-test-static


run-dynamic:
	mkdir -p $(OUTPUT)
	$(BIN)/$(NAME)-test-dynamic


clean:
	rm -f $(OBJ)/* $(BIN)/* $(LIB)/* $(DYLIB)/* $(OUTPUT)/*


install:
	./install.sh $(NAME)


uninstall:
	./uninstall.sh $(NAME)
