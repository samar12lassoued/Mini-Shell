CC = gcc
CFLAGS = -Wall -g
SRC = src/main.c src/parser.c src/executor.c src/execute_built_in_commands.c
INC = -Iinclude

mini-shell: $(SRC) 
	$(CC) $(CFLAGS) $(SRC) -o mini-shell $(INC)

clean:
	rm -f mini-shell