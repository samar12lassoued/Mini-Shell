#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "executor.h"

#define MAX_LINE 1024

int main()
{
    char input[MAX_LINE];

    while (1)
    {
        printf("mini-shell> ");
        fflush(stdout);

        if (!fgets(input, MAX_LINE, stdin))
            break;

        input[strcspn(input, "\n")] = '\0'; 

        char **args = parse_input(input);

        if (args[0] == NULL)
        {
            free(args);
            continue;
        }

        execute_commands(args);

        
        for (int i = 0; args[i] != NULL; i++)
            free(args[i]);
        free(args);
    }

    return 0;
}
