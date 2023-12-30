#include "minishell.h"
#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

// Global variable for exit code
int exit_code = 0;

// Signal handler for SIGINT (Ctrl+C)
void handle_ctrl_c(int sig) 
{
    (void)sig;
    rl_replace_line("", 0);  // Clear the current line
    rl_on_new_line();        // Move the cursor to a new line
    rl_redisplay();          // Redisplay the prompt
}

// Signal handler for SIGQUIT (Ctrl+\)
void handle_ctrl_backslash(int sig) 
{
    (void)sig;
    printf("\nHandling signal with Ctrl+\\ \n");
    exit(exit_code);  // Adjust exit_code as needed
}

// Signal handler for SIGTERM (default termination signal)
void handle_termination(int sig) 
{
    (void)sig;
    printf("\nHandling termination signal \n");
    exit(exit_code);  // Adjust exit_code as needed
}
