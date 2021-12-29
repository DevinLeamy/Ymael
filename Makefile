CC = g++ 
CCFLAGS = -std=c++2a -Wall -MMD

SOURCE = src
INC = -I include -I lib 
BIN = bin
EXEC = main
LIB = -lncurses


SRC = $(wildcard $(SOURCE)/**/*.cc) $(wildcard $(SOURCE)/*.cc)
OBJ = $(SRC:.cc=.o)
DEP = $(SRC:.cc=.d)

main: $(OBJ)
	@mkdir -p $(BIN)
	$(CC) $(CCFLAGS) $(OBJ) $(LIB) -o $(BIN)/main

%.o: %.cc
	$(CC) $(CCFLAGS) $(INC) -c -o $@ $<

-include $(DEP)

.PHONY: clean

clean:
	rm -rf $(OBJ) $(DEP) $(BIN)


