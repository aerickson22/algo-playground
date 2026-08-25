RM=rm -f

CC=gcc
CFLAGS=-g -Wall -Wextra
SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
BINDIR=bin
BIN=$(BINDIR)/min-heap
PACKAGENAME=min-heap.zip

all:$(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run:
	./$(BIN)

clean:
	$(RM) -r bin/* $(OBJ)/*

submit:
	$(RM) $(PACKAGENAME)
	zip $(PACKAGENAME) $(BIN)
