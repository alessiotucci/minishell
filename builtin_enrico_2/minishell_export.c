#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        // Process arguments without using strtok
        int i = 1;
        while (args[i] != NULL) 
        {
            char *arg = args[i];
            char *key = arg;

            // Find the position of '=' in the argument
            char *equal_sign = strchr(arg, '=');

            // If '=' is found and not at the beginning or end
            if (equal_sign != NULL && equal_sign != arg && equal_sign[1] != '\0') 
            {
                *equal_sign = '\0';  // Null-terminate the key
                char *value = equal_sign + 1;

                // Check if the key and value are not empty
                if (*key != '\0' && *value != '\0') 
                {
                    if (setenv(key, value, 1) != 0) 
                    {
                        perror("minishell_export");
                    }
                } 
                else 
                {
                    printf("minishell_export: Invalid format: %s\n", arg);
                }
            } 
            else 
            {
                printf("minishell_export: Invalid format: %s\n", arg);
            }

            i++;
        }
    }
}

int main(int argc, char *argv[]) {
    minishell_export(argv);

    return 0;
}
