#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"
#include "handle_command.h"

#define MAX_LINE 1024

int stop_animation = 0;
char *frames[] = {
    "\033[31m(=^.^=)\033[0m", // red
    "\033[32m(=^o^=)\033[0m", // green
    "\033[34m(=^_^=)\033[0m"  // blue
};

int frame_count = 3;
int current_frame = 0;

char input_buffer[MAX_LINE];
int input_len = 0;

struct termios orig_term;

// ---------------- Terminal ----------------
void reset_terminal()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_term);
}

void enable_raw_mode()
{
    tcgetattr(STDIN_FILENO, &orig_term);
    atexit(reset_terminal);

    struct termios raw = orig_term;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

// ---------------- Animation ----------------
void *animate_cat(void *arg)
{
    while (!stop_animation)
    {
        printf("\rmini-shell %s> %s", frames[current_frame], input_buffer);
        fflush(stdout);
        current_frame = (current_frame + 1) % frame_count;
        usleep(200000);
    }
    return NULL;
}

int main()
{
    enable_raw_mode();

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, animate_cat, NULL);

    int c;
    input_len = 0;
    memset(input_buffer, 0, sizeof(input_buffer));

    while (1)
    {
        c = getchar();

        if (c == '\n')
        { // Enter key
            input_buffer[input_len] = '\0';
            if (input_len > 0)
            {
                // Tokenize input
                char **args = parse_input(input_buffer);

                // Handle built-in or external command
                handle_command(args);

                // Free memory
                for (int i = 0; args[i] != NULL; i++)
                    free(args[i]);
                free(args);
            }

            // Reset input buffer
            input_len = 0;
            memset(input_buffer, 0, sizeof(input_buffer));
            printf("\n"); // move to next line
        }
        else if (c == 127 || c == 8)
        { // Backspace
            if (input_len > 0)
                input_len--;
            input_buffer[input_len] = '\0';
        }
        else
        {
            input_buffer[input_len++] = c;
        }
    }

    stop_animation = 1;
    pthread_join(thread_id, NULL);

    printf("\nBye Bye! See you next time!\n");
    return 0;
}
