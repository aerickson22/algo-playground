RM=rm -f

CC=gcc
CFLAGS=-g -Wall -Wextra
SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
BINDIR=bin
BIN=$(BINDIR)/complexity_plotter
PACKAGENAME=complexity_plotter.zip

all:$(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test:
	./bin/complexity_plotter ./bubble_sort_test 100 5000 100

run:
	@read -p "Enter executable path: " prog; \
	read -p "Enter min: " min; \
	read -p "Enter max: " max; \
	read -p "Enter step: " step; \
	pkill gnuplot 2>/dev/null; true; \
	./bin/complexity_plotter $$prog $$min $$max $$step

clean:
	$(RM) -r bin/* $(OBJ)/*

submit:
	$(RM) $(PACKAGENAME)
	zip $(PACKAGENAME) $(BIN)
