CC = gcc
CFLAGS = -Wall -g
SRC = src/main.c src/parser.c src/executor.c
INC = -Iinclude

mini-shell: $(SRC) 
	$(CC) $(CFLAGS) $(SRC) -o mini-shell $(INC)

clean:
	rm -f mini-shell