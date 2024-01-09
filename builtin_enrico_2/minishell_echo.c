#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libft/libft.h"

void minishell_export(char *args[]) 
{
    // If no arguments provided, print the current environment variables
    if (args[1] == NULL) 
    {
        extern char **environ;
        char **env = environ;
        while (*env != NULL) 
        {
            printf("%s\n", *env);
            env++;
        }
    } 
    else 
    {
        // Iterate through the arguments and set environment variables
        int i = 1;
        while (args[i] != NULL) 
        {
            char **key_value = ft_split(args[i], '=');

            // Check if the format is key=value
            if (key_value && key_value[0] && key_value[1]) 
            {
                if (setenv(key_value[0], key_value[1], 1) != 0) 
                {
                    perror("minishell_export");
                }
                free(key_value);
            } 
            else 
            {
                fprintf(stderr, "minishell_export: Invalid format: %s\n", args[i]);
            }

            i++;
        }
    }
}

int main(int argc, char *argv[]) 
{
    minishell_export(argv);

    return 0;
}
