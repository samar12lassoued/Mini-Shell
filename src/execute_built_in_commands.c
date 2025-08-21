#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "execute_built_in_commands.h"

// -------------------- Built-in implementations --------------------

void builtin_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "mini-shell: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("mini-shell");
        }
    }
}

void builtin_pwd() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("mini-shell");
    }
}

void builtin_echo(char **args) {
    for (int i = 1; args[i] != NULL; i++) {
        printf("%s ", args[i]);
    }
    printf("\n");
}

void builtin_export(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "mini-shell: export requires argument (VAR=VALUE)\n");
        return;
    }
    char *eq = strchr(args[1], '=');
    if (!eq) {
        fprintf(stderr, "mini-shell: export format must be VAR=VALUE\n");
        return;
    }
    *eq = '\0';
    char *name = args[1];
    char *value = eq + 1;
    if (setenv(name, value, 1) != 0) {
        perror("mini-shell");
    }
}

void builtin_unset(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "mini-shell: unset requires a variable name\n");
        return;
    }
    if (unsetenv(args[1]) != 0) {
        perror("mini-shell");
    }
}
