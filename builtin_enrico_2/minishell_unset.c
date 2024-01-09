/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enricogiraldi <enricogiraldi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:16:44 by enricogiral       #+#    #+#             */
/*   Updated: 2024/01/09 17:18:36 by enricogiral      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Function to implement the 'unset' built-in
void minishell_unset(char *variable_name, char *envp[]) 
{
    char **env = envp;
    int found = 0;

    // Find the variable in the environment
    while (*env != NULL) 
    {
        if (strncmp(*env, variable_name, strlen(variable_name)) == 0 &&
            (*env)[strlen(variable_name)] == '=') 
        {
            found = 1;
            break;
        }
        env++;
    }

    // If the variable is found, unset it
    if (found) {
        for (char **p = env; *p != NULL; p++) 
        {
            *p = *(p + 1);
        }
        printf("Unset variable: %s\n", variable_name);
    } 
    else 
    {
        printf("Variable not found: %s\n", variable_name);
    }
}

// Main function for testing the minishell_unset function
int main(int argc, char *argv[], char *envp[]) 
{
    if (argc != 2) 
    {
        printf("Usage: %s VARIABLE_NAME\n", argv[0]);
        return 1;
    }

    char *variable_name = argv[1];

    // Call the minishell_unset function
    minishell_unset(variable_name, envp);

    return 0;
}
