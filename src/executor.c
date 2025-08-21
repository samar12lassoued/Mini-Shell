#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "executor.h"
#include "execute_built_in_commands.h"

void execute_commands(char **args) {
    if (args[0] == NULL) return;

    // Handle built-ins
    if (strcmp(args[0], "exit") == 0) exit(0);
    if (strcmp(args[0], "cd") == 0) { builtin_cd(args); return; }
    if (strcmp(args[0], "pwd") == 0) { builtin_pwd(); return; }
    if (strcmp(args[0], "echo") == 0) { builtin_echo(args); return; }
    if (strcmp(args[0], "export") == 0) { builtin_export(args); return; }
    if (strcmp(args[0], "unset") == 0) { builtin_unset(args); return; }

    // External commands
    pid_t pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1) perror("mini-shell");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
    } else {
        perror("fork");
    }
}
