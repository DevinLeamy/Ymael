CC = g++ 
CCFLAGS = -std=c++2a -Wall -MMD

SOURCE = src
INC = -I include 
LIB = lib
BIN = bin
EXEC = main


SRC = $(wildcard $(SOURCE)/**/*.cc) $(wildcard $(SOURCE)/*.cc)
OBJ = $(SRC:.cc=.o)
DEP = $(SRC:.cc=.d)

main: $(OBJ)
	@mkdir -p $(BIN)
	$(CC) $(CCFLAGS) $(OBJ) -o $(BIN)/main

%.o: %.cc
	$(CC) $(CCFLAGS) $(INC) -c -o $@ $<

.PHONY: clean

clean:
	rm -rf $(OBJ) $(DEP) $(BIN)


