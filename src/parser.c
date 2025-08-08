#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

#define MAX_TOKENS 64

char **parse_input(char *line)
{
    char **tokens = malloc(MAX_TOKENS * sizeof(char *));
    if (!tokens)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    char *token = strtok(line, " ");
    int i = 0;

    while (token != NULL && i < MAX_TOKENS - 1)
    {
        tokens[i++] = strdup(token);
        token = strtok(NULL, " ");
    }
    tokens[i] = NULL;

    return tokens;
}
