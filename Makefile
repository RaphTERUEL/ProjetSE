CC = gcc
CFLAGS = -g -std=c99 -pedantic -Werror -Wall -Wextra
OBJECT = src/main.c src/terminal.c src/filesystem.c src/primitives.c
NAME = myshell 

all: $(OBJECT)
	$(CC) $(CFLAGS) $^ -o $(NAME)

clean: 
	rm -f $(NAME) *.o
