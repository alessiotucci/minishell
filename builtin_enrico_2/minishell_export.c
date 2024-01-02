#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void minishell_export(char *args[]) 
{
    // If no arguments provided, print the current environment variables
    if (args[1] == NULL) 
    {
        extern char **environ;
        for (char **env = environ; *env != NULL; env++) 
        {
            printf("%s\n", *env);
        }
    } else {
        // Iterate through the arguments and set environment variables
        for (int i = 1; args[i] != NULL; i++) 
        {
            char *key = strtok(args[i], "=");
            char *value = strtok(NULL, "");

            // Check if the format is key=value
            if (key != NULL && value != NULL) 
            {
                if (setenv(key, value, 1) != 0) 
                {
                    perror("minishell_export");
                }
            } 
            else 
            {
                fprintf(stderr, "minishell_export: Invalid format: %s\n", args[i]);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    minishell_export(argv);

    return 0;
}

