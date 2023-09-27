CC = gcc
INCLUDES = includes
SOURCES = src/*.c
BINARY = ./main
PROG = main.c
FLAGS = -g -lm -Wall -Werror
VFLAGS = --show-leak-kinds=all --track-origins=yes --leak-check=full -s

all:
	@$(CC) -o $(BINARY) $(PROG) $(SOURCES) -I $(INCLUDES) $(FLAGS)

run:
	@$(BINARY)
