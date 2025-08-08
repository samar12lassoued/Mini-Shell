#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "executor.h"

void execute_commands(char **args)
{
    if (strcmp(args[0], "exit") == 0)
    {
        exit(0);
    }

    pid_t pid = fork();

    if (pid == 0)
    {
        // child process
        if (execvp(args[0], args) == -1)
        {
            perror("mini-shell");
        }
        exit(EXIT_FAILURE); // In case execvp fails
    }
    else if (pid > 0)
    {
        // parent process
        int status;
        waitpid(pid, &status, 0);
    }
    else
    {
        perror("fork");
    }
}
