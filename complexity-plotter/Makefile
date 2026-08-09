RM=rm -f
CC=gcc
CFLAGS=-g -Wall -Wextra
SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
BINDIR=bin
BIN=$(BINDIR)/complexity-plotter
PACKAGENAME=complexity-plotter.zip
all:$(BIN)
release: CFLAGS=-Wall -Wextra -O2 -DNDEBUG
release: clean
release: $(BIN)
$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o main
$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	$(RM) -r bin/* $(OBJ)/*
submit:
	$(RM) $(PACKAGENAME)
	zip $(PACKAGENAME) $(BIN)
