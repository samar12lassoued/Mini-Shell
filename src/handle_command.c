#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "execute_built_in_commands.h"
#include "executor.h"

int handle_command(char **args)
{
    if (args[0] == NULL)
        return 1;

    if (strcmp(args[0], "cd") == 0)
    {
        builtin_cd(args);
        return 1;
    }
    else if (strcmp(args[0], "pwd") == 0)
    {
        builtin_pwd();
        return 1;
    }
    else if (strcmp(args[0], "echo") == 0)
    {
        builtin_echo(args);
        return 1;
    }
    else if (strcmp(args[0], "export") == 0)
    {
        builtin_export(args);
        return 1;
    }
    else if (strcmp(args[0], "unset") == 0)
    {
        builtin_unset(args);
        return 1;
    }
    else if (strcmp(args[0], "exit") == 0)
    {
        exit(0);
    }

    // Not a built-in, execute external command
    execute_commands(args);
    return 1;
}
